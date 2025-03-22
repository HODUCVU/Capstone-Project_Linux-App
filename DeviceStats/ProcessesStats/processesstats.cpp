#include "processesstats.h"
#include "../../utils/processcommand.h"

ProcessesStats::ProcessesStats() : ExecuteProcessStatsCommand() {}

void ProcessesStats::getProcessStatsFromDevice()
{
    QString command = getprocessesInfoCommand();
    QString output = ProcessCommand::execute(command);
    QStringList processesInfo = output.split("\n");
    extractProcessesInfo(processesInfo);
}

void ProcessesStats::extractProcessesInfo(QStringList lines)
{
    for(QString &stats:lines) {
        QStringList info = stats.split(" ");
        QString PName = info[0];
        QString user = info[1];
        int PID = info[2].toInt();
        float PCPUUsagePercent = info[3].toFloat();
        float PMEMUsagePercent = info[4].toFloat();
        this->processesStats[PName] = ProcessStats(PName, user, PID, PCPUUsagePercent, PMEMUsagePercent);
    }
}
