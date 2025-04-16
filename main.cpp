#include "TCPService/tcpservice.h"
// #include "TCPService/senderworker.h"
// #include "testing.h"
// #include "OverloadSolution/stresstestsystem.h"
// #include "DeviceStats/SystemStats/systemmem.h"
// #include "DeviceStats/ProcessesStats/processesstats.h"

#include <QCoreApplication>
// #include <QObject>
// #include <QTimer>
// #include <QDir>
int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // SystemMEM mem;
    // ProcessesStats pStats;
    // pStats.getProcessStatsFromDevice();
    TcpService service;
    service.start();
    return a.exec();
}
