#include "TCPService/tcpservice.h"
#include "TCPService/senderworker.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    TcpService service;
    return a.exec();
}
