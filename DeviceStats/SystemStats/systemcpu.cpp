#include "systemcpu.h"
#include "../../utils/processcommand.h"
#include <QDebug>

SystemCPU::SystemCPU(QObject *parent)
    : QObject(parent), ExecuteCPUCoreCommand() {
    getNumberOfCoreCPUFromDevice();
    setupCores();
}

void SystemCPU::setupCores()
{
    for(int i = 0; i < CPUCore::numberOfCore; i++)
        this->cores.append(CPUCore(i));
}

SystemCPU::~SystemCPU()
{
    this->cores.clear();
}

float SystemCPU::getCPUUtilization()
{
    return this->CPUUtilization;
}

void SystemCPU::getNumberOfCoreCPUFromDevice()
{
    QString command = getnumberOfCoreCPUCommand();
    QString output = ProcessCommand::execute(command);
    CPUCore::numberOfCore = output.toInt();
}

void SystemCPU::getCPUUtilizationStatsFromDevice()
{
    QString command = getCPUUtilizationCommand();
    QString output = ProcessCommand::execute(command);
    this->CPUUtilization = output.split("\n").first().toFloat();
    qDebug() << "%CPU: " << CPUUtilization;
}

void SystemCPU::getCoresCPUUtilizationStatsFromDevice()
{
    QString command = getcoreCPUUtilizationCommand();
    QString output = ProcessCommand::execute(command);
    QStringList lines = output.split("\n");
    extractCoresCPUUsageInfo(lines);
}
void SystemCPU::extractCoresCPUUsageInfo(QStringList lines)
{
    // for(const QString &info: lines) {
    //     QStringList coreInfo = info.split(" ");
    //     int coreID = coreInfo[0].toInt();
    //     float coreCPUUsage = coreInfo[1].toFloat();
    //     this->cores[coreID].setCoreCPUUtilization(coreCPUUsage);
    //     qDebug() << "%CPU Core " << coreID << ": " << coreCPUUsage;
    // }

    // Có một cách khác, đó là cho i từ 0 đến numberOfCore, dù gì thì coreID cũng được sắp xếp rồi
    for(int i = 0; i < lines.size(); i++) {
        float coreCPUUsage = lines[i].toFloat();
        this->cores[i].setCoreCPUUtilization(coreCPUUsage);
        qDebug() << "%CPU Core " << i << ": " << coreCPUUsage;
    }
}

void SystemCPU::getCoresTemperatureStatsFromDevice()
{
    QString command = getcoreTemperatureCommand();
    QString output = ProcessCommand::execute(command);
    QStringList lines = output.split("\n");
    extractCoresTemperatureInfo(lines);
}
void SystemCPU::extractCoresTemperatureInfo(QStringList lines)
{
    int LogicalCore = this->cores.size()/2;
    for(int i = 0; i < lines.size(); i++) {
        lines[i].remove("+").remove("°C");
        float temperature = lines[i].toFloat();
        this->cores[i].setCoreTemperature(temperature);
        this->cores[LogicalCore++].setCoreTemperature(temperature);
        qDebug() << "Temperature Core " << i << ": " << temperature;
    }
}

void SystemCPU::getCoresFrequencyStatsFromDevice()
{

}


