// #include "TCPService/tcpservice.h"
#include "TCPService/senderworker.h"
#include "OverloadSolution/stresstestsystem.h"
#include "testing.h"
#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    // TcpService tcpService;
    // tcpService.start();
    SenderWorker sender;
    Testing testing;
    QTimer timer;

    QObject::connect(&timer, &QTimer::timeout, [&sender, &testing]() {
        // sender.collectStats();
        // qDebug() << "State: " << testing.overloadingDetectAdvance(*(sender.systemStats));
    });
    timer.start(1000);
    // StressTestSystem stressTest;
    // stressTest.setup(2, 60, 8, 60);
    // stressTest.start();
    return a.exec();
}
