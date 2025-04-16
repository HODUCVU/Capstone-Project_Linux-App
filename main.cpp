#include "TCPService/tcpservice.h"
#include "TCPService/senderworker.h"
// #include "testing.h"
#include "OverloadSolution/stresstestsystem.h"

#include <QCoreApplication>
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    TcpService service;
    service.start();
    // StressTestSystem stresstest;
    // stresstest.setup(2, 80, 8, 30);
    // stresstest.start();
    return a.exec();
}
