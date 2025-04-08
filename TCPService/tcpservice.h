#ifndef TCPSERVICE_H
#define TCPSERVICE_H

#include "senderworker.h"
#include "receiverworker.h"
#include <QTcpSocket>
#include <QThread>

class TcpService : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;
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
private slots:
    void writeToSocket(const QJsonObject &obj);
    void onReadyRead();
private:
    void establishSocket();
    void establishSenderThread();
    void establishReceiverThread();
};

#endif // TCPSERVICE_H
