#include "tcpservice.h"
#include "../utils/hostIPAddress.h"
#include <QDebug>
#include <QJsonDocument>
#include <QByteArray>

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
    if (socket) {
        socket->disconnectFromHost();
        socket->deleteLater();
    };
    if(reconnectToServer)
        reconnectToServer->deleteLater();
}

void TcpService::establishSocket()
{
    socket = new QTcpSocket(this);
    socket->connectToHost(HOST,PORT);
    autoReconnectToServerIfFail();
}

void TcpService::autoReconnectToServerIfFail()
{
    reconnectToServer = new QTimer(this);
    reconnectToServer->setInterval(TIME_TO_TRY_RECONNECT_TO_SEVER);
    connect(socket, &QTcpSocket::connected, this, [=]() {
        qDebug() << "Tcp Service connected";
        establishSenderThread();
        establishReceiverThread();
        reconnectToServer->stop();
        reconnectToServer->deleteLater();
    });
    connect(socket, &QTcpSocket::errorOccurred, this, [=](){
        qDebug() << "Connection failed, will retry...";
        if(reconnectToServer && !reconnectToServer->isActive())
            reconnectToServer->start();
    });
    connect(reconnectToServer, &QTimer::timeout, this, [=](){
        qDebug() << "Attempting to reconnect...";
        socket->abort();
        socket->connectToHost(HOST, PORT);
    });
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
    connect(this, &TcpService::messageReceived, receiver, &ReceiverWorker::handleMessage, Qt::QueuedConnection);
    connect(&receiverThread, &QThread::finished, receiver, &QObject::deleteLater);
}

void TcpService::start()
{
    senderThread.start();
    receiverThread.start();
}

void TcpService::writeToSocket(const QJsonObject &obj)
{
    if(socket && socket->isOpen()) {
        QJsonDocument doc(obj);
        socket->write(doc.toJson(QJsonDocument::Compact) + '\n');
        // socket->flush();
    }
}

void TcpService::onReadyRead()
{
    while(socket->canReadLine()) {
        QByteArray data = socket->readLine();
        QString message = QString::fromUtf8(data.trimmed());
        qDebug() << message;
        emit messageReceived(message);
    }
}

