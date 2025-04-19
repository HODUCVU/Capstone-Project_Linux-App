#include "TCPService/tcpservice.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    TcpService service;
    service.start();

    return a.exec();
}
