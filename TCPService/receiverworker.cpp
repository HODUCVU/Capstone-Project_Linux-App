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

void ReceiverWorker::handleWarningAlert()
{
    speaker->alertUserViaSound(3, 500, 150);
}

void ReceiverWorker::terminate(const QJsonObject &obj)
{
    QString PName = obj["PName"].toString();
    qDebug() << "Kill" << PName;
    terminateProcesses->terminateProcessByPName(PName);
}

inline void ReceiverWorker::alertSpeaker()
{
    speaker->alertUserViaSound();
}
