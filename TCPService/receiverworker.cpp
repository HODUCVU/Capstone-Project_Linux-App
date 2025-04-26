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

void ReceiverWorker::handleKillProcess(const QJsonObject &obj)
{
    qDebug() << "Terminate Process";
    terminate(obj);
    alertSpeaker();
}
void ReceiverWorker::handleStopStress() {
    qDebug() << "Stop Stress Testing System";
    stressTest->stop();
}

void ReceiverWorker::terminate(const QJsonObject &obj)
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
