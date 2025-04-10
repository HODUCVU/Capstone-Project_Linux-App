#include "TCPService/tcpservice.h"
#include "TCPService/senderworker.h"
#include "OverloadSolution/stresstestsystem.h"
#include <QCoreApplication>
#include <QObject>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    // TcpService tcpService;
    // tcpService.start();
    SenderWorker sender;
    sender.run();
    // StressTestSystem stressTest;
    // stressTest.setup(1, 100, 8, 60);
    // stressTest.start();
    return a.exec();
}
