#ifndef RECEIVERWORKER_H
#define RECEIVERWORKER_H

#include "../OverloadSolution/terminateprocesses.h"
#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>

class ReceiverWorker : public QObject
{
    Q_OBJECT
private:
    QTcpSocket socket;
    TerminateProcesses terminateProcesses;
public:
    explicit ReceiverWorker(QObject *parent=nullptr);
public slots:
    void run();
    void onReadyRead();
signals:
    void messagesReceived(const QStringList &PNames);
private:
    void parseMessage(QString &message);
    bool authMessage(QJsonDocument &doc);
    void terminate(QJsonObject &obj);

};

#endif // RECEIVERWORKER_H
