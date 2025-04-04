// #include "testing.h"
// #include <QDebug>
// Testing::Testing(QObject *parent)
//     : QObject(parent)
// {
//     connect(&timer, &QTimer::timeout, this, &Testing::collectStats);
// }

// void Testing::start()
// {
//     timer.start(1000);
// }

// void Testing::collectStats()
// {
//     collectGeneralCPUStats();
//     collectCoreCPUStats();
//     collectMEMStats();
//     collectProcessesStats();
// }

// void Testing::testingGeneralCPUStats()
// {
//     collectGeneralCPUStats();
//     printGeneralCPUStats(systemStats.CPUStats.general);
// }

// void Testing::collectGeneralCPUStats()
// {

//     systemStats.CPUStats.getCPUUtilizationStatsFromDevice();
//     systemStats.CPUStats.getCPUTemperatureStatsFromDevice();
//     systemStats.CPUStats.getCPUFrequencyPercentFromDevice();
// }
// void Testing::printGeneralCPUStats(CPUGeneral general)
// {
//     qDebug() << "***********************************";
//     qDebug() << "%CPU\tTemperature\tFrequency";
//     qDebug() << general.getCPUUtilization() << "\t"
//              << general.getCPUTemperature() << "\t"
//              << general.getCPUFrequency() << " ("
//              << general.getCPUFrequencyPercent() << ")";
// }

// void Testing::testingCoreCPUStats()
// {
//     collectCoreCPUStats();
//     qDebug() << "***********************************";
//     qDebug() << "ID\t %CPU\tTemp\t Freq";
//     for(auto &core: systemStats.CPUStats.cores)
//         printCoreCPUStats(core);
// }

// void Testing::collectCoreCPUStats()
// {
//     systemStats.CPUStats.getCoresCPUUtilizationStatsFromDevice();
//     systemStats.CPUStats.getCoresTemperatureStatsFromDevice();
//     systemStats.CPUStats.getCoresFrequencyStatsFromDevice();
// }
// void Testing::printCoreCPUStats(CPUCore core)
// {
//     qDebug() << core.getCoreID() << "\t"
//              << core.getCoreCPUUilization() << "\t"
//              << core.getCoreTemperature() << "\t"
//              << core.getCoreFrequency();
// }

// void Testing::testingMEMStats()
// {
//     collectMEMStats();
//     printMEMSats(systemStats.MEMStats);
// }

// void Testing::collectMEMStats()
// {
//     systemStats.MEMStats.getMEMUtilizationFromDevice();
// }
// void Testing::printMEMSats(SystemMEM MEM)
// {
//     qDebug() << "***********************************";
//     qDebug() << "\tUsed(MB)\tPercent";
//     qDebug() << "RAM\t" << MEM.getRAMUtilization() << "\t" << MEM.getRAMUtilizationPercent();
//     qDebug() << "SWAP\t" << MEM.getSWAPMEMUtilization() << "\t" << MEM.getSWAPMEMUtilizationPercent();
// }

// void Testing::testingProcessesStats()
// {
//     collectProcessesStats();
//     printProcessesStats();
// }

// void Testing::collectProcessesStats()
// {
//     processes.getProcessStatsFromDevice();
// }
// void Testing::printProcessesStats()
// {
//     qDebug() << "User\tPID\t%CPU\tMEM\t%MEM\tCommand";
//     for(auto it = processes.processesStats.begin(); it != processes.processesStats.end(); ++it) {
//         qDebug() << it.value().getUser() << "\t"
//                  << it.value().getPID() << "\t"
//                  << it.value().getPCPUUsagePercent()/8.0 << "%\t"
//                  << it.value().getPMEMUsageMB() << "MB\t"
//                  << it.value().getPMEMUsagePercent()<< "%\t"
//                  << it.value().getPName();
//     }
//     qDebug() << "***********************************";
// }

// void Testing::testingTerminateProcesses()
// {
//     QStringList PNames = {"brave", "chrome"};
//     terminateCommand.getPNamsFromMessage(PNames);
//     terminateCommand.terminateProcessByPName();
// }
