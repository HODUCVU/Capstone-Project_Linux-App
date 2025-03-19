#include "systemcpu.h"
#include "../../utils/processcommand.h"
#include <QDebug>

SystemCPU::SystemCPU(QObject *parent)
    : QObject(parent), ExecuteCPUCoreCommand() {
    getNumberOfCoreCPUFromDevice();
    setupCores();
    getFrequencyMaxMinFromDevice();
}

void SystemCPU::getNumberOfCoreCPUFromDevice()
{
    QString command = getnumberOfCoreCPUCommand();
    QString output = ProcessCommand::execute(command);
    CPUCore::numberOfCore = output.toInt();
}
void SystemCPU::setupCores()
{
    for(int i = 0; i < CPUCore::numberOfCore; i++)
        this->cores.append(CPUCore(i));
}

void SystemCPU::getFrequencyMaxMinFromDevice()
{
    QString command = getCPUFrequencyMaxMinCommand();
    QString output = ProcessCommand::execute(command);
    QStringList lines = output.split("\n");
    this->CPUFrequencyMax = lines[0].toFloat();
    this->CPUFrequencyMin = lines[1].toFloat();
}

SystemCPU::~SystemCPU()
{
    this->cores.clear();
}

float SystemCPU::getCPUUtilization()
{
    return this->CPUUtilization;
}
float SystemCPU::getCPUTemperature()
{
    return this->CPUTemperature;
}
float SystemCPU::getCPUFrequencyPercent()
{
    return this->CPUFrequencyPercent;
}
float SystemCPU::getCPUFrequency()
{
    float range = (this->CPUFrequencyMax - this->CPUFrequencyMin);
    return this->CPUFrequencyMin + range*this->CPUFrequencyPercent/100;
}

void SystemCPU::getCPUUtilizationStatsFromDevice()
{
    QString command = getCPUUtilizationCommand();
    QString output = ProcessCommand::execute(command);
    this->CPUUtilization = output.split("\n").first().toFloat();
}

void SystemCPU::getCPUTemperatureStatsFromDevice()
{
    QString command = getCPUTemperatureCommand();
    QString output = ProcessCommand::execute(command);
    this->CPUTemperature = output.remove("+").remove("°C").toFloat();
}

void SystemCPU::getCPUFrequencyPercentFromDevice()
{
    QString command = getCPUFrequencyPercentCommand();
    QString output = ProcessCommand::execute(command);
    this->CPUFrequencyPercent = output.remove("%").toFloat();
}

void SystemCPU::getCoresCPUUtilizationStatsFromDevice()
{
    QString command = getcoreCPUUtilizationCommand();
    QString output = ProcessCommand::execute(command);
    QStringList cpuUsageValues = output.split("\n");
    extractCoresCPUUsageInfo(cpuUsageValues);
}
void SystemCPU::extractCoresCPUUsageInfo(QStringList lines)
{
    for(int i = 0; i < lines.size(); i++) {
        float coreCPUUsage = lines[i].toFloat();
        this->cores[i].setCoreCPUUtilization(coreCPUUsage);
        // qDebug() << "%CPU Core " << i << ": " << coreCPUUsage;
    }
}

void SystemCPU::getCoresTemperatureStatsFromDevice()
{
    QString command = getcoreCPUTemperatureCommand();
    QString output = ProcessCommand::execute(command);
    QStringList tempValues = output.split("\n");
    extractCoresCPUTemperatureInfo(tempValues);
}
void SystemCPU::extractCoresCPUTemperatureInfo(QStringList lines)
{
    int LogicalCore = this->cores.size()/2;
    for(int physicalCore = 0; physicalCore < lines.size(); physicalCore++) {
        lines[physicalCore].remove("+").remove("°C");
        float temperature = lines[physicalCore].toFloat();
        this->cores[physicalCore].setCoreTemperature(temperature);
        this->cores[LogicalCore++].setCoreTemperature(temperature);
        // qDebug() << "Temperature Core " << i << ": " << temperature;
    }
}

void SystemCPU::getCoresFrequencyStatsFromDevice()
{
    QString command = getcoreCPUFrequencyCommand();
    QString output = ProcessCommand::execute(command);
    QStringList freqValues = output.split("\n");
    extractCoreCPUFrequencyInfo(freqValues);
}

void SystemCPU::extractCoreCPUFrequencyInfo(QStringList lines)
{
    for(int i = 0; i < lines.size(); i++) {
        float freqMHz = lines[i].toFloat()/1000.0;
        this->cores[i].setCoreFrequency(freqMHz);
        qDebug() << "Freq core " << i << ": " << freqMHz << " MHz";
    }
}

void SystemCPU::testtingCPUStats()
{
    getCPUUtilizationStatsFromDevice();
    getCPUTemperatureStatsFromDevice();
    getCPUFrequencyPercentFromDevice();
    qDebug() << "%CPU: " << this->CPUUtilization;
    qDebug() << "Temperature: " << this->CPUTemperature;
    qDebug() << "Max Freq: " << this->CPUFrequencyMax << " Min Freq: " << this->CPUFrequencyMin;
    qDebug() << "Frequency: " << getCPUFrequency() << "MHz occupied: "<< this->CPUFrequencyPercent << "%" ;
}


