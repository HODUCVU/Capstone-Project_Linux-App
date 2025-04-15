// #include "TCPService/tcpservice.h"
#include "TCPService/senderworker.h"
#include "testing.h"
#include "OverloadSolution/stresstestsystem.h"
#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include <QDir>
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // TcpService service;
    // service.start();
    // SenderWorker sender;
    // Testing testing;
    // QTimer timer;
    // QObject::connect(&timer, &QTimer::timeout, [&sender, &testing](){
    //     sender.collectStats();
    //     testing.processesFilter(*(sender.processesStats));
    // });
    // timer.start(500);
    // StressTestSystem stressTest;
    // stressTest.setup(2,70,8,60);
    // stressTest.start();

    return a.exec();
}
