#ifndef SYSTEMCPU_H
#define SYSTEMCPU_H
#include "../../utils/commands.h"
#include "cpucore.h"
#include "cpugeneral.h"
#include <QObject>

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
    void getCPUFrequencyPercentFromDevice();

    void getCoresCPUUtilizationStatsFromDevice();
    void getCoresTemperatureStatsFromDevice();
    void getCoresFrequencyStatsFromDevice();
private:
    void getNumberOfCoreCPUFromDevice();
    void setupCores();
    void getFrequencyMaxMinFromDevice();

    void extractCoresCPUUsageInfo(QStringList lines);
    void extractCoresCPUTemperatureInfo(QStringList lines);
    void extractCoreCPUFrequencyInfo(QStringList lines);
};

#endif // SYSTEMCPU_H
