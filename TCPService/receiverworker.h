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
    void handleMessage(const QString &message);
private:
    bool authMessage(QJsonDocument &doc);
    void terminate(QJsonObject &obj);
    void alertSpeaker();
    void stress(QJsonObject &obj);
};

#endif // RECEIVERWORKER_H
