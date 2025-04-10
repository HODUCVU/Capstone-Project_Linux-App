#include "systemcpu.h"
#include "../../utils/processcommand.h"

SystemCPU::SystemCPU()
    : ExecuteCPUCoreCommand()
{
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
    this->general.CPUFrequencyMax = lines[0].toFloat();
    this->general.CPUFrequencyMin = lines[1].toFloat();
}

SystemCPU::~SystemCPU()
{
    this->cores.clear();
}

void SystemCPU::getCPUUtilizationStatsFromDevice()
{
    QString command = getCPUUtilizationCommand();
    QString output = ProcessCommand::execute(command);
    QStringList cpuUsageValues = output.split("\n");
    extractCPUUsageInfo(cpuUsageValues);
}

void SystemCPU::getCPUTemperatureStatsFromDevice()
{
    QString command = getCPUTemperatureCommand();
    QString output = ProcessCommand::execute(command);
    this->general.CPUTemperature = output.remove("+").remove("°C").toFloat();
}

void SystemCPU::getCPUFrequencyPercentFromDevice()
{
    QString command = getCPUFrequencyPercentCommand();
    QString output = ProcessCommand::execute(command);
    this->general.CPUFrequencyPercent = output.remove("%").toFloat();
}

void SystemCPU::extractCPUUsageInfo(QStringList lines)
{
    this->general.CPUUtilization = lines[0].toFloat();
    for(int i = 1; i < lines.size(); i++) {
        float coreCPUUsage = lines[i].toFloat();
        this->cores[i].coreCPUUtilization = coreCPUUsage;
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
        this->cores[physicalCore].coreTemperature = temperature;
        this->cores[LogicalCore++].coreTemperature = temperature;
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
        this->cores[i].coreFrequency = freqMHz;
    }
}

