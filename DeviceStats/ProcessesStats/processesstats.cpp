#include "processesstats.h"
#include "../../utils/processcommand.h"
#include "../SystemStats/systemmem.h" // for SystemMEM::maxRAMSystem
#include "../SystemStats/cpucore.h" // for CPUCore::numberOfCore

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
