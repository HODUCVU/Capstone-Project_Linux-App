#include "TCPService/tcpservice.h"
#include "TCPService/senderworker.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    qDebug() << "Hello, Welcome to Monitoring and Balance IVI System Software\n";
    TcpService service;
    return a.exec();
}
