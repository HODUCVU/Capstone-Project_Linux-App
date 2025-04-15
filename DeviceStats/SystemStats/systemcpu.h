#ifndef SYSTEMCPU_H
#define SYSTEMCPU_H

#include "../../utils/commands.h"
#include "cpucore.h"
#include "cpugeneral.h"
#include <QVector>

class SystemCPU : public ExecuteCPUCoreCommand
{
public:
    QVector<CPUCore> cores;
    CPUGeneral general;
public:
    SystemCPU();
    ~SystemCPU();

    // Get stats from device
    void getCPUUtilizationStatsFromDevice();
    void getCPUTemperatureStatsFromDevice();
    void getCoresTemperatureStatsFromDevice();
    void getCPUFrequencyPercentFromDevice();
    void getCoresFrequencyStatsFromDevice();
private:
    void getNumberOfCoreCPUFromDevice();
    void setupCores();
    void getFrequencyMaxMinFromDevice();

    void extractCPUUsageInfo(QStringList lines);
    void extractCoresCPUTemperatureInfo(QStringList lines);
    void extractCoreCPUFrequencyInfo(QStringList lines);
};

#endif // SYSTEMCPU_H
