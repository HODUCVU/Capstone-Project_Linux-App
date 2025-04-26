#ifndef RECEIVERWORKER_H
#define RECEIVERWORKER_H

#include "../OverloadSolution/terminateprocesses.h"
#include "../OverloadSolution/devicespeaker.h"
#include "../OverloadSolution/stresstestsystem.h"
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

class ReceiverWorker : public QObject
{
    Q_OBJECT
private:
    TerminateProcesses *terminateProcesses;
    DeviceSpeaker *speaker;
    StressTestSystem *stressTest;
public:
    explicit ReceiverWorker(QObject *parent=nullptr);
    ~ReceiverWorker();
public slots:
    void handleKillProcess(const QJsonObject &obj);
    void handleStopStress();
private:
    void terminate(const QJsonObject &obj);
    void alertSpeaker();
    void establishStressTest();
};

#endif // RECEIVERWORKER_H
