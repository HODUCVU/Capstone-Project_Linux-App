#include "senderworker.h"
#include <QDateTime>

#define TIMEOUT_COLLECTION 1000

SenderWorker::SenderWorker(QObject *parent)
    : QObject(parent)
{
    timer = nullptr;
    systemStats = new SystemStats();
    processesStats = new ProcessesStats();
}

SenderWorker::~SenderWorker()
{
    timer->stop();
    delete timer;
    delete systemStats;
    delete processesStats;
}

void SenderWorker::run()
{
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &SenderWorker::collectStats);
    timer->start(TIMEOUT_COLLECTION);
}

void SenderWorker::collectStats()
{
    collectSystemStats(); // 1s
    collectProcessesStats();
    currentDateTime();
    sendStats();
}

void SenderWorker::collectSystemStats()
{
    collectCPUStats();
    collectMEMStats();
}
void SenderWorker::collectCPUStats()
{
    systemStats->CPUStats.getCPUUtilizationStatsFromDevice(); //1s
    systemStats->CPUStats.getCPUTemperatureStatsFromDevice();
    systemStats->CPUStats.getCoresTemperatureStatsFromDevice();
    systemStats->CPUStats.getCPUFrequencyPercentFromDevice();
    systemStats->CPUStats.getCoresFrequencyStatsFromDevice();
}
void SenderWorker::collectMEMStats()
{
    systemStats->MEMStats.getMEMUtilizationFromDevice();
}

void SenderWorker::collectProcessesStats()
{
    processesStats->getProcessStatsFromDevice();
}

void SenderWorker::currentDateTime()
{
    timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
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
    generalCPU["CPUUtilization"] = systemStats->CPUStats.general.getCPUUtilization();
    generalCPU["CPUTemperature"] = systemStats->CPUStats.general.getCPUTemperature();
    generalCPU["CPUFrequency"] = systemStats->CPUStats.general.getCPUFrequency();
    generalCPU["CPUFrequencyPercent"] = systemStats->CPUStats.general.getCPUFrequencyPercent();
    return generalCPU;
}

QJsonObject SenderWorker::systemCoresCPUToJson() {
    QJsonObject coresCPU;
    for(CPUCore core:systemStats->CPUStats.cores) {
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
    MEM["RAMUsage"] = systemStats->MEMStats.getRAMUtilization();
    MEM["RAMPercent"] = systemStats->MEMStats.getRAMUtilizationPercent();
    MEM["MaxRAM"] = SystemMEM::maxRAMSystem;
    MEM["SWAPUsage"] = systemStats->MEMStats.getSWAPMEMUtilization();
    MEM["SWAPPercent"] = systemStats->MEMStats.getSWAPMEMUtilizationPercent();
    MEM["MaxSWAP"] = SystemMEM::maxSWAPMEMSystem;
    return MEM;
}

QJsonObject SenderWorker::processesStatsToJson()
{
    QJsonObject PStats;
    for(ProcessStats process:processesStats->processes) {
        if(process.getPCPUUsagePercent() > 0 || process.getPMEMUsagePercent() > 0) {
            QJsonObject info;
            info["PID"] = process.getPID();
            info["User"] = process.getUser();
            info["PName"] = process.getPName();
            info["PCPUUsagePercent"] = process.getPCPUUsagePercent();
            info["PMEMUsagePercent"] = process.getPMEMUsagePercent();
            info["PMEMUsageMB"] = process.getPMEMUsageMB();
            PStats[QString::number(process.getPID())] = info;
        }
    }
    return PStats;
}

void SenderWorker::printProcesses()
{
    QString temptimestamp1 = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    qDebug() << temptimestamp1 ;
    collectProcessesStats();
    temptimestamp1 = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    qDebug() << temptimestamp1 ;
    for(auto &p:processesStats->processes) {
        if(p.getPCPUUsagePercent() > 0 || p.getPMEMUsagePercent() > 0) {
            p.print();
        }
    }
}
