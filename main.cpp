#include "DeviceStats/SystemStats/systemcpu.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    // Khi khởi động thì chạy install.sh
    SystemCPU systemCPU;

    QTimer timer;
    // QObject::connect(&timer, &QTimer::timeout, &systemCPU, &SystemCPU::getCPUUtilizationStatsFromDevice);
    // QObject::connect(&timer, &QTimer::timeout, &systemCPU, &SystemCPU::getCoresCPUUtilizationStatsFromDevice);
    // QObject::connect(&timer, &QTimer::timeout, &systemCPU, &SystemCPU::testtingCPUStats);
    QObject::connect(&timer, &QTimer::timeout, &systemCPU, &SystemCPU::testtingCoreCPUStats);
    timer.start(1000);

    return a.exec();
}
