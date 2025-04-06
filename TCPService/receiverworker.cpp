#include "receiverworker.h"
#include "../utils/hostIPAddress.h"
#include <QJsonArray>
#include <QByteArray>
#include <QString>

ReceiverWorker::ReceiverWorker(QObject *parent)
    : QObject(parent){}

void ReceiverWorker::run()
{
    socket.connectToHost(HOST, PORT);
    if(socket.waitForConnected(TIME_WAIT_TO_CONNECT_TO_SERVER)) {
        connect(&socket, &QTcpSocket::readyRead, this, &ReceiverWorker::onReadyRead);
    }
}

void ReceiverWorker::onReadyRead()
{
    while(socket.canReadLine()) {
        QByteArray data = socket.readLine();
        QString message = QString::fromUtf8(data.trimmed());
        parseMessage(message);
    }
}

void ReceiverWorker::parseMessage(QString &message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if(!authMessage(doc)) return;
    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();
    if(type == "PNames") {
        terminate(obj);
    }
}

bool ReceiverWorker::authMessage(QJsonDocument &doc)
{
    if(!doc.isObject()) {
        return false;
    }
    return true;
}

void ReceiverWorker::terminate(QJsonObject &obj)
{
    if(!(obj.contains("PNames") && obj["PNames"].isArray())) return;
    QJsonArray PNameArray = obj["PNames"].toArray();
    for(const QJsonValue &val:PNameArray) {
        terminateProcesses.terminateProcessByPName(val.toString());
    }
}


