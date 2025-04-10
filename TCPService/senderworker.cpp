#include "senderworker.h"
#include <QDateTime>

#define TIMEOUT_COLLECTION 200

SenderWorker::SenderWorker(QObject *parent)
    : QObject(parent), timer(nullptr), systemStats(SystemStats()), processesStats(ProcessesStats())
{}

SenderWorker::~SenderWorker()
{
    timer->stop();
}

void SenderWorker::run()
{
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &SenderWorker::collectStats);
    timer->start(TIMEOUT_COLLECTION);
}

void SenderWorker::collectStats()
{
    collectSystemStats(); // 2s
    collectProcessesStats();
    currentDateTime();
    sendStats();
    print();
}

void SenderWorker::currentDateTime()
{
    timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}

void SenderWorker::collectSystemStats()
{
    collectGeneralCPUStats(); // 1s
    collectCoreCPUStats(); // 1s
    collectMEMStats();
}
void SenderWorker::collectGeneralCPUStats()
{
    systemStats.CPUStats.getCPUUtilizationStatsFromDevice(); //1s
    systemStats.CPUStats.getCPUTemperatureStatsFromDevice();
    systemStats.CPUStats.getCPUFrequencyPercentFromDevice();
}
void SenderWorker::collectCoreCPUStats()
{
    systemStats.CPUStats.getCoresCPUUtilizationStatsFromDevice();
    systemStats.CPUStats.getCoresTemperatureStatsFromDevice();
    systemStats.CPUStats.getCoresFrequencyStatsFromDevice();
}
void SenderWorker::collectMEMStats()
{
    systemStats.MEMStats.getMEMUtilizationFromDevice();
}

void SenderWorker::collectProcessesStats()
{
    processesStats.getProcessStatsFromDevice();
}

void SenderWorker::sendStats()
{
    QJsonObject obj;
    obj["timestamp"] = timestamp;
    obj["SystemStats"] = systemStatsToJson();
    obj["ProcessesStats"] = processesStatsToJson();
    emit sendMessage(obj);

}

QJsonObject SenderWorker::systemStatsToJson() {
    QJsonObject SStats;
    SStats["GeneralCPU"] = systemGeneralCPUToJson();
    SStats["coresCPU"] = systemCoresCPUToJson();
    SStats["MEM"] = systemMEMToJson();
    return SStats;
}
QJsonObject SenderWorker::systemGeneralCPUToJson()
{
    QJsonObject generalCPU;
    generalCPU["CPUUtilization"] = systemStats.CPUStats.general.getCPUUtilization();
    generalCPU["CPUTemperature"] = systemStats.CPUStats.general.getCPUTemperature();
    generalCPU["CPUFrequency"] = systemStats.CPUStats.general.getCPUFrequency();
    generalCPU["CPUFrequencyPercent"] = systemStats.CPUStats.general.getCPUFrequencyPercent();
    return generalCPU;
}

QJsonObject SenderWorker::systemCoresCPUToJson() {
    QJsonObject coresCPU;
    for(CPUCore core:systemStats.CPUStats.cores) {
        QJsonObject coreCPU;
        coreCPU["CPUUtilization"] = core.getCoreCPUUtilization();
        coreCPU["CPUTemperature"] = core.getCoreTemperature();
        coreCPU["CPUFrequency"] = core.getCoreFrequency();
        coresCPU[QString::number(core.getCoreID())] = coreCPU;
    }
    return coresCPU;
}

QJsonObject SenderWorker::systemMEMToJson()
{
    QJsonObject MEM;
    MEM["RAM"] = systemStats.MEMStats.getRAMUtilization();
    MEM["RAMPercent"] = systemStats.MEMStats.getRAMUtilizationPercent();
    MEM["SWAP"] = systemStats.MEMStats.getSWAPMEMUtilization();
    MEM["SWAPPercent"] = systemStats.MEMStats.getSWAPMEMUtilizationPercent();
    return MEM;
}

QJsonObject SenderWorker::processesStatsToJson()
{
    QJsonObject PStats;
    for(ProcessStats process:processesStats.processes) {
        if(process.getPCPUUsagePercent() > 0 && process.getPMEMUsagePercent() > 0) {
            QJsonObject info;
            info["PID"] = process.getPID();
            info["User"] = process.getUser();
            info["PName"] = process.getPName();
            info["PCPUUsagePercent"] = process.getPCPUUsagePercent();
            info["PMEMUsageMB"] = process.getPMEMUsageMB();
            info["PMEMUsagePercent"] = process.getPMEMUsagePercent();
            PStats[QString::number(process.getPID())] = info;
        }
    }
    return PStats;
}

#include <QDebug>
void SenderWorker::print()
{
    qDebug() << "Time: " << timestamp;
}

