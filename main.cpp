#include "TCPService/tcpservice.h"
#include <QCoreApplication>
#include <QObject>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    TcpService tcpService;
    tcpService.start();
    return a.exec();
}
