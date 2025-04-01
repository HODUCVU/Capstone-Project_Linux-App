#include "testing.h"
#include <QDebug>
Testing::Testing(QObject *parent)
    : QObject(parent)
{
    connect(&timer, &QTimer::timeout, this, &Testing::testingProcessesStats);
}

void Testing::start()
{
    timer.start(100);
}

void Testing::testingGeneralCPUStats()
{
    systemStats.CPUStats.getCPUUtilizationStatsFromDevice();
    systemStats.CPUStats.getCPUTemperatureStatsFromDevice();
    systemStats.CPUStats.getCPUFrequencyPercentFromDevice();
    printGeneralCPUStats(systemStats.CPUStats.general);
}
void Testing::printGeneralCPUStats(CPUGeneral general)
{
    qDebug() << "***********************************";
    qDebug() << "%CPU\tTemperature\tFrequency";
    qDebug() << general.getCPUUtilization() << "\t"
             << general.getCPUTemperature() << "\t"
             << general.getCPUFrequency() << " ("
             << general.getCPUFrequencyPercent() << ")";
}

void Testing::testingCoreCPUStats()
{
    systemStats.CPUStats.getCoresCPUUtilizationStatsFromDevice();
    systemStats.CPUStats.getCoresTemperatureStatsFromDevice();
    systemStats.CPUStats.getCoresFrequencyStatsFromDevice();
    qDebug() << "***********************************";
    qDebug() << "ID\t %CPU\tTemp\t Freq";
    for(auto &core: systemStats.CPUStats.cores)
        printCoreCPUStats(core);
}
void Testing::printCoreCPUStats(CPUCore core)
{
    qDebug() << core.getCoreID() << "\t"
             << core.getCoreCPUUilization() << "\t"
             << core.getCoreTemperature() << "\t"
             << core.getCoreFrequency();
}

void Testing::testingMEMStats()
{
    systemStats.MEMStats.getMEMUtilizationFromDevice();
    printMEMSats(systemStats.MEMStats);
}
void Testing::printMEMSats(SystemMEM MEM)
{
    qDebug() << "***********************************";
    qDebug() << "\tUsed(MB)\tPercent";
    qDebug() << "RAM\t" << MEM.getRAMUtilization() << "\t" << MEM.getRAMUtilizationPercent();
    qDebug() << "SWAP\t" << MEM.getSWAPMEMUtilization() << "\t" << MEM.getSWAPMEMUtilizationPercent();
}

void Testing::testingProcessesStats()
{
    processes.getProcessStatsFromDevice();
    printProcessesStats();
}
void Testing::printProcessesStats()
{
    qDebug() << "User\tPID\t%CPU\tMEM\t%MEM\tCommand";
    for(auto it = processes.processesStats.begin(); it != processes.processesStats.end(); ++it) {
        qDebug() << it.value().getUser() << "\t"
                 << it.value().getPID() << "\t"
                 << it.value().getPCPUUsagePercent()/8.0 << "%\t"
                 << it.value().getPMEMUsageMB() << "MB\t"
                 << it.value().getPMEMUsagePercent()<< "%\t"
                 << it.value().getPName();
    }
    qDebug() << "***********************************";
}

void Testing::testingTerminateProcesses()
{
    QStringList PNames = {"brave", "chrome"};
    terminateCommand.getPNamsFromMessage(PNames);
    terminateCommand.terminateProcessByPName();
}
