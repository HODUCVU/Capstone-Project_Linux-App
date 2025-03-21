#include "systemstats.h"
#include <QDebug>

SystemStats::SystemStats(QObject *parent)
    : QObject(parent)
{
    CPUStats = SystemCPU();
    MEMStats = SystemMEM();
    NetworkIOStats = SystemNetworkIO();
}

void SystemStats::testingCPUStats()
{
    CPUStats.getCPUUtilizationStatsFromDevice();
    CPUStats.getCPUTemperatureStatsFromDevice();
    CPUStats.getCPUFrequencyPercentFromDevice();
    printCPUStats();
}

void SystemStats::printCPUStats()
{
    qDebug() << "*****************************";
    qDebug() << "%CPU: " << CPUStats.getCPUUtilization() << "%";
    qDebug() << "Temperature: " << CPUStats.getCPUTemperature();
    qDebug() << "Frequency: " << CPUStats.getCPUFrequency()
             << "MHz occupied: "<< CPUStats.getCPUFrequencyPercent() << "%" ;
}

void SystemStats::testingCoreCPUStats()
{
    CPUStats.getCoresCPUUtilizationStatsFromDevice();
    CPUStats.getCoresTemperatureStatsFromDevice();
    CPUStats.getCoresFrequencyStatsFromDevice();
    printCoreCPUStats();
}

void SystemStats::printCoreCPUStats()
{
    for(auto &core:CPUStats.cores) {
        qDebug() << "*****************************";
        qDebug() << "Core " << core.getCoreID();
        qDebug() << "\t%CPU: " << core.getCoreCPUUilization();
        qDebug() << "\t%Temperature: " << core.getCoreTemperature();
        qDebug() << "\t%Frequency: " << core.getCoreFrequency();
    }
}

void SystemStats::testingMEMUStats()
{
    MEMStats.getMEMUtilizationFromDevice();
    qDebug() << "*****************************";
    qDebug() << "Max MEM" << "\tMEM Usage" << "\tOccupied";
    qDebug() << SystemMEM::maxMEMSystem << "\t" << MEMStats.getMEMUtilization() << "\t" << MEMStats.getMEMUtilizationPercent();
}

void SystemStats::testingNetworkIDStats()
{
    NetworkIOStats.getNetworkReceiveFromDevice();
    NetworkIOStats.getNetworkSendFromDevice();
    qDebug() << "*****************************";
    qDebug() << "Receiving: " << NetworkIOStats.getReceivingSpeed() << "Kb/s"
             << "\tSending: " << NetworkIOStats.getSendingSpeed() << "Kb/s";
    qDebug() << "Total Received: " << NetworkIOStats.getTotalReceivedMB() << "MB"
             << "Total Sent: " << NetworkIOStats.getTotalSentMB() << "MB";

}
