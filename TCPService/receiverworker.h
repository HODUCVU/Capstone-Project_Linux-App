#ifndef RECEIVERWORKER_H
#define RECEIVERWORKER_H

#include "../OverloadSolution/terminateprocesses.h"
#include "../OverloadSolution/devicespeaker.h"
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

class ReceiverWorker : public QObject
{
    Q_OBJECT
private:
    TerminateProcesses terminateProcesses;
    DeviceSpeaker speaker;
public:
    explicit ReceiverWorker(QObject *parent=nullptr);
public slots:
    void handleMessage(const QString &message);
private:
    bool authMessage(QJsonDocument &doc);
    void terminate(QJsonObject &obj);
    void alertSpeaker();
};

#endif // RECEIVERWORKER_H
