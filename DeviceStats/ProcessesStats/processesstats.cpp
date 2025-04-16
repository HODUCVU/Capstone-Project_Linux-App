#include "processesstats.h"
#include "../../utils/processcommand.h"
#include "../SystemStats/cpucore.h"
#include <QDebug>

ProcessesStats::ProcessesStats()
    : ExecuteProcessStatsCommand() {}

ProcessesStats::~ProcessesStats()
{
    this->processes.clear();
}

void ProcessesStats::getProcessStatsFromDevice()
{
    this->processes.clear();
    QString command = getprocessesInfoCommand();
    QString output = ProcessCommand::execute(command);
    QStringList processesInfo = output.split("\n");
    extractProcessesInfo(processesInfo);
}

// void ProcessesStats::extractProcessesInfo(QStringList &lines)
// {
//     int i = 0, idx = 0;
//     for(; i < lines.size(); i++) {
//         if(lines[i].isEmpty()) break;
//         this->processes.append(ProcessStats());
//         extractCPUInfo(lines[i], idx);
//         idx++;
//     }
//     i+=2; idx = 0;
//     for(; i < lines.size(); i++) {
//         extractMEMInfo(lines[i],idx);
//         idx++;
//     }
// }
// void ProcessesStats::extractCPUInfo(QString &line, int idx) {
//     QStringList info = line.simplified().split(" ");
//     int UID = info[2].toInt();
//     this->processes[idx].user = whoami(UID);
//     this->processes[idx].PID = info[3].toInt();
//     this->processes[idx].PCPUUsagePercent = info[8].toFloat()/8;
//     this->processes[idx].PName = info[10];
// }

// void ProcessesStats::extractMEMInfo(QString &line, int idx)
// {
//     QStringList info = line.simplified().split(" ");
//     this->processes[idx].PMENUsageMB = info[7].toFloat()/1024.0;
//     this->processes[idx].PMEMUsagePercent = info[8].toFloat();
// }
// QString ProcessesStats::whoami(int UID) {
//     switch (UID) {
//         case 0: return "root";
//         case 1000: return "normal";
//         default: return "other";
//     }
// }

void ProcessesStats::extractProcessesInfo(QStringList &lines)
{
    for(QString &processStats:lines) {
        QStringList info = processStats.simplified().split(" ");
        QString PName = info[0];
        QString user = info[1];
        int PID = info[2].toInt();
        float PCPUUsagePercent = info[3].toFloat()/CPUCore::numberOfCore;
        float PMEMUsagePercent = info[4].toFloat();
        float PMEMMB = SystemMEM::maxRAMSystem*PMEMUsagePercent/100;
        this->processes.append(ProcessStats(PName, user, PID, PCPUUsagePercent, PMEMUsagePercent, PMEMMB));
    }
}
