#include "TCPService/tcpservice.h"
// #include "TCPService/senderworker.h"
#include <QCoreApplication>
#include <QObject>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    TcpService tcpService;
    tcpService.start();
    // SenderWorker sender;
    // sender.run();
    return a.exec();
}
