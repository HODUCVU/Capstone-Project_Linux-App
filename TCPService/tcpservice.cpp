#include "tcpservice.h"


TcpService::TcpService(QObject *parent)
    : QObject(parent)
{
    establishSenderThread();
    establishReceiverThread();
}

TcpService::~TcpService()
{
    senderThread.quit();
    senderThread.wait();
    receiverThread.quit();
    receiverThread.wait();
}

void TcpService::start()
{
    senderThread.start();
    receiverThread.start();
}

void TcpService::establishSenderThread()
{
    sender = new SenderWorker();
    sender->moveToThread(&senderThread);
    connect(&senderThread, &QThread::started, sender, &SenderWorker::run);
    connect(&senderThread, &QThread::finished, sender, &QObject::deleteLater);
}

void TcpService::establishReceiverThread()
{
    receiver = new ReceiverWorker();
    receiver->moveToThread(&receiverThread);
    connect(&receiverThread, &QThread::started, receiver, &ReceiverWorker::run);
    connect(&receiverThread, &QThread::finished, receiver, &QObject::deleteLater);
    connect(receiver, &ReceiverWorker::messagesReceived, this, &TcpService::messageReceived);
}
