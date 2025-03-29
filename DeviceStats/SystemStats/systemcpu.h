#ifndef SYSTEMCPU_H
#define SYSTEMCPU_H
#include "../../utils/commands.h"
#include "cpucore.h"
#include <QObject>
class SystemCPU : public ExecuteCPUCoreCommand
{
public:
    QVector<CPUCore> cores;
private:
    float CPUUtilization;
    float CPUTemperature;
    float CPUFrequencyPercent;
    float CPUFrequencyMax;
    float CPUFrequencyMin;
public: // Getter
    float getCPUUtilization();
    float getCPUTemperature();
    float getCPUFrequencyPercent();
    float getCPUFrequency();

public:
    SystemCPU();
    ~SystemCPU();

    // Get stats from device
    void getCPUUtilizationStatsFromDevice();
    void getCPUTemperatureStatsFromDevice();
    void getCPUFrequencyPercentFromDevice();

    void getNumberOfCoreCPUFromDevice();
    void getCoresCPUUtilizationStatsFromDevice();
    void getCoresTemperatureStatsFromDevice();
    void getCoresFrequencyStatsFromDevice();

private:
    void setupCores();
    void getFrequencyMaxMinFromDevice();
    void extractCoresCPUUsageInfo(QStringList lines);
    void extractCoresCPUTemperatureInfo(QStringList lines);
    void extractCoreCPUFrequencyInfo(QStringList lines);
};

#endif // SYSTEMCPU_H
