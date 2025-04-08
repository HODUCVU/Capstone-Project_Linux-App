#include "receiverworker.h"
#include "../utils/hostIPAddress.h"
#include <QJsonArray>
#include <QString>
#include <QDebug>

ReceiverWorker::ReceiverWorker(QObject *parent)
    : QObject(parent){}

void ReceiverWorker::handleMessage(const QString &message)
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
