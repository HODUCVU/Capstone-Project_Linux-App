#include "processesstats.h"
#include "../../utils/processcommand.h"
#include <QDebug>

ProcessesStats::ProcessesStats(QObject *parent)
    : QObject(parent), ExecuteProcessStatsCommand() {}

ProcessesStats::~ProcessesStats()
{
    this->processesStats.clear();
}

void ProcessesStats::getProcessStatsFromDevice()
{
    this->processesStats.clear();
    QString command = getprocessesInfoCommand();
    QString output = ProcessCommand::execute(command);
    QStringList processesInfo = output.split("\n");
    extractProcessesInfo(processesInfo);
}

void ProcessesStats::extractProcessesInfo(QStringList lines)
{
    for(QString &processStats:lines) {
        // qDebug() << processStats;
        QStringList info = processStats.simplified().split(" ");
        QString PName = info[0];
        QString user = info[1];
        int PID = info[2].toInt();
        float PCPUUsagePercent = info[3].toFloat();
        float PMEMUsagePercent = info[4].toFloat();
        // qDebug() << info[0] << " " << info[1] << " " << info[2] << " " << info[3] << " " << info[4];
        updateProcessStats(ProcessStats(PName, user, PID, PCPUUsagePercent, PMEMUsagePercent));
    }
}
void ProcessesStats::updateProcessStats(ProcessStats processStats)
{
    auto it = this->processesStats.find(processStats.getPName());
    if(it != this->processesStats.end()) {
        it->setPCPUUsagePercent(
            it->getPCPUUsagePercent() + processStats.getPCPUUsagePercent());
        it->setPMEMUsagePercent(
            it->getPMEMUsagePercent() + processStats.getPMEMUsagePercent());
    }
    else
        this->processesStats.insert(processStats.getPName(), processStats);
}

void ProcessesStats::testingProcessesStats()
{
    getProcessStatsFromDevice();
    qDebug() << "User\tPID\t%CPU\tMEM\t%MEM\tCommand";
    for(auto it = processesStats.begin(); it != processesStats.end(); ++it) {
        qDebug() << it.value().getUser() << "\t"
                 << it.value().getPID() << "\t"
                 << it.value().getPCPUUsagePercent()/8.0 << "%\t"
                 << it.value().getPMEMUsageMB() << "MB\t"
                 << it.value().getPMEMUsagePercent()*100 << "%\t"
                 << it.value().getPName();
    }
    qDebug() << "***********************************";
}
