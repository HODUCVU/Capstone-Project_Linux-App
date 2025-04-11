#include "TCPService/tcpservice.h"
// #include "TCPService/senderworker.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    TcpService service;
    service.start();
    // SenderWorker sender;
    // sender.run();
    return a.exec();
}
