#include "receiverworker.h"
#include "../utils/hostIPAddress.h"
#include <QJsonArray>
#include <QString>

ReceiverWorker::ReceiverWorker(QObject *parent)
    : QObject(parent)
{
    terminateProcesses = new TerminateProcesses();
    speaker = new DeviceSpeaker();
    stressTest = new StressTestSystem();
}

ReceiverWorker::~ReceiverWorker()
{
    delete terminateProcesses;
    delete speaker;
    delete stressTest;
}

void ReceiverWorker::handleMessage(const QString &message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if(!authMessage(doc)) return;
    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();
    if(type == "PNames") {
        alertSpeaker();
        terminate(obj);
    } else if(type == "startStress") {
        stress(obj);
        stressTest->start();
    } else if(type == "stopStress") {
        stressTest->stop();
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
        qDebug() << "PName: " << val.toString();
        terminateProcesses->terminateProcessByPName(val.toString());
    }
}

void ReceiverWorker::alertSpeaker()
{
    speaker->alertUserViaSound();
}

void ReceiverWorker::stress(QJsonObject &obj)
{
    int numbeOfTaskToRun = obj["numberOfTaskToRun"].toInt();
    float MEMUsagePercent = obj["MEMUsagePercent"].toDouble();
    int numberOfCore = obj["numberOfCore"].toInt();
    float timeout = obj["timeout"].toDouble();
    stressTest->setup(numbeOfTaskToRun, MEMUsagePercent, numberOfCore, timeout);
}
