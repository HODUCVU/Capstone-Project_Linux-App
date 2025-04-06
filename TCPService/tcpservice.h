#ifndef TCPSERVICE_H
#define TCPSERVICE_H

#include "senderworker.h"
#include "receiverworker.h"
#include <QThread>
#include <QString>

class TcpService : public QObject
{
    Q_OBJECT
private:
    QThread senderThread;
    QThread receiverThread;
    SenderWorker *sender;
    ReceiverWorker *receiver;
public:
    explicit TcpService(QObject *parent = nullptr);
    ~TcpService();
    void start();
signals:
    void messageReceived(const QString &message);
private:
    void establishSenderThread();
    void establishReceiverThread();
};

#endif // TCPSERVICE_H
