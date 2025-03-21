#include "DeviceStats/SystemStats/systemstats.h"

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Khi khởi động thì chạy install.sh
    SystemStats systemStats;
    QTimer timer;
    // QObject::connect(&timer, &QTimer::timeout, &systemCPU, &SystemCPU::testtingCPUStats);
    // QObject::connect(&timer, &QTimer::timeout, &systemCPU, &SystemCPU::testtingCoreCPUStats);
    // QObject::connect(&timer, &QTimer::timeout, &systemMEM, &SystemMEM::testingMEMUStats);
    // QObject::connect(&timer, &QTimer::timeout, &systemStats, &SystemStats::testingCPUStats);
    // QObject::connect(&timer, &QTimer::timeout, &systemStats, &SystemStats::testingCoreCPUStats);
    // QObject::connect(&timer, &QTimer::timeout, &systemStats, &SystemStats::testingMEMUStats);
    QObject::connect(&timer, &QTimer::timeout, &systemStats, &SystemStats::testingNetworkIDStats);
    timer.start(1000);

    return a.exec();
}
