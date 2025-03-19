#include "DeviceStats/SystemStats/systemcpu.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    SystemCPU systemCPU;

    QTimer timer;
    // QObject::connect(&timer, &QTimer::timeout, &systemCPU, &SystemCPU::getCPUUtilizationStatsFromDevice);
    // QObject::connect(&timer, &QTimer::timeout, &systemCPU, &SystemCPU::getCoresCPUUtilizationStatsFromDevice);
    QObject::connect(&timer, &QTimer::timeout, &systemCPU, &SystemCPU::getCoresTemperatureStatsFromDevice);
    // QObject::connect(&timer, &QTimer::timeout, [&](){
    //     systemCPU.getCPUUtilizationStatsFromDevice();
    //     systemCPU.getCoresCPUUtilizationStatsFromDevice();
    // });
    timer.start(1000);

    return a.exec();
}
