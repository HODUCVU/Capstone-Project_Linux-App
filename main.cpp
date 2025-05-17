#include "TCPService/tcpservice.h"
#include "TCPService/senderworker.h"
#include <QCoreApplication>
#include <QTimer>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    TcpService service;

    return a.exec();
}
