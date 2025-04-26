#ifndef TCPSERVICE_H
#define TCPSERVICE_H

#include "senderworker.h"
#include "receiverworker.h"
#include "../OverloadSolution/stresstestsystem.h"
#include <QTcpSocket>
#include <QThread>

class TcpService : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;
    QThread senderThread;
    QThread receiverThread;
    QThread stressTestThread;
    SenderWorker *sender;
    ReceiverWorker *receiver;
    StressTestSystem *stressTest;
public:
    explicit TcpService(QObject *parent = nullptr);
    ~TcpService();
    void start();
signals:
    void killProcess(const QJsonObject &obj);
    void startStress(const QJsonObject &obj);
    void stopStress();
private slots:
    void writeToSocket(const QJsonObject &obj);
    void onReadyRead();
    // void disconnectedFromServer();
private:
    void establishSocket();
    void establishSenderThread();
    void establishReceiverThread();
    void establishStressTestThread();
    void handleTypeMessage(const QString &msg);
};

#endif // TCPSERVICE_H
