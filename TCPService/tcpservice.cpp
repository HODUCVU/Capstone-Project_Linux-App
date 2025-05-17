#include "tcpservice.h"
#include "../utils/hostIPAddress.h"
#include <QDebug>
#include <QJsonDocument>
#include <QByteArray>
#include <QNetworkDatagram>
#include <QUdpSocket>

TcpService::TcpService(QObject *parent)
    : QObject(parent)
{
    establishSocket();
}

TcpService::~TcpService()
{
    senderThread.quit();
    senderThread.wait();
    receiverThread.quit();
    receiverThread.wait();
    stressTestThread.quit();
    stressTestThread.wait();
    if (socket) {
        socket->disconnectFromHost();
        socket->deleteLater();
    };
}

void TcpService::establishSocket()
{
    QUdpSocket *udpDiscovery = new QUdpSocket(this);
    udpDiscovery->bind(QHostAddress::AnyIPv4, PORT);

    connect(udpDiscovery, &QUdpSocket::readyRead, this, [=]() {
        while (udpDiscovery->hasPendingDatagrams()) {
            QNetworkDatagram datagram = udpDiscovery->receiveDatagram();
            QString msg = datagram.data();
            if (msg.startsWith("SERVER")) {
                QString portStr = msg.split(":").value(1);
                quint16 port = portStr.toUShort();
                QHostAddress serverAddress = datagram.senderAddress();

                qDebug() << "Discovered server at:" << serverAddress.toString() << ":" << port;

                socket = new QTcpSocket(this);
                socket->connectToHost(serverAddress, port);
                if(socket->waitForConnected(TIME_WAIT_TO_CONNECT_TO_SERVER)) {
                    udpDiscovery->close();
                    udpDiscovery->deleteLater();
                    qDebug() << "Tcp Service connected";
                    establishSenderThread();
                    establishReceiverThread();
                    establishStressTestThread();
                    start();
                    return;

                }
            }
        }
    });
    // Send broadcast to find server
    QByteArray discovery = "DISCOVER_SERVER";
    udpDiscovery->writeDatagram(discovery, QHostAddress::Broadcast, 45000);
}

void TcpService::establishSenderThread()
{
    sender = new SenderWorker();
    sender->moveToThread(&senderThread);
    connect(sender, &SenderWorker::sendMessage, this, &TcpService::writeToSocket, Qt::QueuedConnection);
    connect(&senderThread, &QThread::started, sender, &SenderWorker::run);
    connect(&senderThread, &QThread::finished, sender, &QObject::deleteLater);
}

void TcpService::establishReceiverThread()
{
    receiver = new ReceiverWorker();
    receiver->moveToThread(&receiverThread);

    connect(socket, &QTcpSocket::readyRead, this, &TcpService::onReadyRead);
    connect(this, &TcpService::killProcess, receiver, &ReceiverWorker::handleKillProcess, Qt::QueuedConnection);
    connect(this, &TcpService::stopStress, receiver, &ReceiverWorker::handleStopStress, Qt::QueuedConnection);
    connect(&receiverThread, &QThread::finished, receiver, &QObject::deleteLater);
}

void TcpService::establishStressTestThread()
{
    stressTest = new StressTestSystem();
    stressTest->moveToThread(&stressTestThread);
    connect(this, &TcpService::startStress, stressTest, &StressTestSystem::start, Qt::QueuedConnection);
    connect(&stressTestThread, &QThread::finished, stressTest, &QObject::deleteLater);
}

void TcpService::start()
{
    senderThread.start();
    receiverThread.start();
    stressTestThread.start();
}

void TcpService::writeToSocket(const QJsonObject &obj)
{
    if(socket && socket->isOpen()) {
        QJsonDocument doc(obj);
        socket->write(doc.toJson(QJsonDocument::Compact) + '\n');
    }
}

void TcpService::onReadyRead()
{
    while(socket->canReadLine()) {
        QByteArray data = socket->readLine();
        QString message = QString::fromUtf8(data.trimmed());
        qDebug() << message;
        handleTypeMessage(message);
    }
}
void TcpService::handleTypeMessage(const QString &msg) {
    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());
    if(!doc.isObject()) return;
    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();
    if(type == "killProcess") emit killProcess(obj);
    else if(type == "startStress") emit startStress(obj);
    else if(type == "stopStress") emit stopStress();
}
