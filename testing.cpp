// #include "testing.h"
// #include <QDebug>
// #include <QFile>

// #define OVERLOADING 50
// #define WARNING 45

// #define WEIGHT_RAM 0.25
// #define WEIGHT_SWAP 0.25
// #define WEIGHT_CPU_USAGE 0.2
// #define WEIGHT_CPU_CORE_USAGE 0.15
// #define WEIGHT_CPU_TEMP 0.05
// #define WEIGHT_CPU_CORE_TEMP 0.05
// #define WEIGHT_CPU_FEQ 0.05

// #define TEMP_MIN 40
// #define TEMP_MAX 90

// #define DATA_PATH_WHILELIST "../../Datasheet/WhileList.txt"
// #define DATA_PATH_PRIORITY "../../Datasheet/PRIORITY.txt"

// Testing::Testing(QObject *parent)
//     : QObject(parent)
// {}

// int Testing::overloadingDetectAdvance(SystemStats &systemStats)
// {
//     double systemCPUUsagePercent = systemStats.CPUStats.general.getCPUUtilization();
//     double systemCPUTemperatue = systemStats.CPUStats.general.getCPUTemperature();
//     double systemCPUFreqPercent = systemStats.CPUStats.general.getCPUFrequencyPercent();
//     double avgCPUCoreUsagePercent = 0.0;
//     double avgCPUCoreTemperature = 0.0;
//     for(auto &core:systemStats.CPUStats.cores) {
//         avgCPUCoreUsagePercent += core.getCoreCPUUtilization();
//         avgCPUCoreTemperature += core.getCoreTemperature();
//     }
//     avgCPUCoreUsagePercent /= CPUCore::numberOfCore;
//     avgCPUCoreTemperature /= CPUCore::numberOfCore;

//     double RAMUsagePercent = systemStats.MEMStats.getRAMUtilizationPercent();
//     double SWAPUsagePercent = systemStats.MEMStats.getSWAPMEMUtilizationPercent();

//     // convert fom temp scale to percent scale
//     double normSystemCPUTemp = std::clamp((systemCPUTemperatue - TEMP_MIN)/(TEMP_MAX - TEMP_MIN)*100, 0.0, 100.0);
//     double normAvgCPUCoreTemp = std::clamp((avgCPUCoreTemperature - TEMP_MIN)/(TEMP_MAX - TEMP_MIN)*100, 0.0, 100.0);

//     double score =
//         WEIGHT_RAM*RAMUsagePercent +
//         WEIGHT_SWAP*SWAPUsagePercent +
//         WEIGHT_CPU_USAGE*systemCPUUsagePercent +
//         WEIGHT_CPU_CORE_USAGE*avgCPUCoreUsagePercent +
//         WEIGHT_CPU_TEMP*normSystemCPUTemp +
//         WEIGHT_CPU_CORE_TEMP*normAvgCPUCoreTemp +
//         WEIGHT_CPU_FEQ*systemCPUFreqPercent;
//     qDebug() << systemCPUUsagePercent << systemCPUFreqPercent << normSystemCPUTemp
//              << avgCPUCoreUsagePercent << normAvgCPUCoreTemp
//              << RAMUsagePercent << SWAPUsagePercent
//              << "Score:" << score;
//     if(score >= OVERLOADING)
//         return (int)LoadLevel::STATE_OVERLOADED;
//     else if(score >= WARNING)
//         return (int)LoadLevel::STATE_WARNING;
//     return (int)LoadLevel::STATE_NORMAL;

// }

// void Testing::processesFilter(ProcessesStats &processesStats)
// {
//     QSet<QString> PNames;
//     QVector<ProcessStats*> filtered;

//     // B1: Lọc tiến trình không phải root (filter 1)
//     for (auto &process : processesStats.processes) {
//         if (process.getUser() != "root") {
//             QString name = process.getPName();
//             PNames.insert(name);
//             filtered.append(&process);
//         }
//     }

//     // B2: Lọc theo whitelist (filter 2)
//     QFile whitelistFile(DATA_PATH_WHILELIST);
//     if (whitelistFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         QTextStream in(&whitelistFile);
//         while (!in.atEnd()) {
//             QString line = in.readLine().trimmed();
//             if (!line.isEmpty())
//                 PNames.remove(line);
//         }
//         whitelistFile.close();
//     }

//     // B3: Đọc file priority
//     QHash<QString, int> priorityMap = readPriority();

//     // B4: Tính điểm tiến trình (filter 3)
//     QVector<QPair<QString, float>> ranked;

//     for (ProcessStats *proc : filtered) {
//         QString name = proc->getPName();
//         if (!PNames.contains(name))
//             continue;

//         float cpu = proc->getPCPUUsagePercent();
//         float mem = proc->getPMEMUsagePercent();
//         int prio = priorityMap.value(name, 2); // mặc định pr = 2 nếu không có

//         float score = 0.4f * cpu + 0.4f * mem + 0.2f * prio;
//         ranked.append({name, score});
//     }

//     // B5: Xếp hạng và lấy top tiến trình
//     std::sort(ranked.begin(), ranked.end(),
//               [](const auto &a, const auto &b) {
//                   return a.second > b.second;
//               });

//     QStringList toKill;
//     for (int i = 0; i < qMin(maxKillCount, ranked.size()); ++i)
//         toKill << ranked[i].first;

//     // B6: Gửi danh sách tiến trình cần kill đến Linux App với cấu trúc Json như define
// }

// QHash<QString, int> Testing::readPriority()
// {
//     QHash<QString, int> priorities;
//     QFile file(DATA_PATH_PRIORITY);
//     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         qWarning() << "Can't open priority file:" << DATA_PATH_PRIORITY;
//         return priorities;
//     }

//     QTextStream in(&file);
//     while (!in.atEnd()) {
//         QString line = in.readLine().trimmed();
//         if (line.isEmpty()) continue;

//         QStringList parts = line.split(":");
//         if (parts.size() != 2) continue;

//         QString name = parts[0].trimmed();
//         int pr = parts[1].toInt();
//         priorities[name] = pr;
//     }

//     file.close();
//     return priorities;
// }
