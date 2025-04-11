#include "testing.h"
#include <QDebug>

#define OVERLOADING 50
#define WARNING 45

#define WEIGHT_RAM 0.25
#define WEIGHT_SWAP 0.25
#define WEIGHT_CPU_USAGE 0.2
#define WEIGHT_CPU_CORE_USAGE 0.15
#define WEIGHT_CPU_TEMP 0.05
#define WEIGHT_CPU_CORE_TEMP 0.05
#define WEIGHT_CPU_FEQ 0.05

#define TEMP_MIN 40
#define TEMP_MAX 90

Testing::Testing(QObject *parent)
    : QObject(parent)
{}

int Testing::overloadingDetectAdvance(SystemStats &systemStats)
{
    double systemCPUUsagePercent = systemStats.CPUStats.general.getCPUUtilization();
    double systemCPUTemperatue = systemStats.CPUStats.general.getCPUTemperature();
    double systemCPUFreqPercent = systemStats.CPUStats.general.getCPUFrequencyPercent();
    double avgCPUCoreUsagePercent = 0.0;
    double avgCPUCoreTemperature = 0.0;
    for(auto &core:systemStats.CPUStats.cores) {
        avgCPUCoreUsagePercent += core.getCoreCPUUtilization();
        avgCPUCoreTemperature += core.getCoreTemperature();
    }
    avgCPUCoreUsagePercent /= CPUCore::numberOfCore;
    avgCPUCoreTemperature /= CPUCore::numberOfCore;

    double RAMUsagePercent = systemStats.MEMStats.getRAMUtilizationPercent();
    double SWAPUsagePercent = systemStats.MEMStats.getSWAPMEMUtilizationPercent();

    // convert fom temp scale to percent scale
    double normSystemCPUTemp = std::clamp((systemCPUTemperatue - TEMP_MIN)/(TEMP_MAX - TEMP_MIN)*100, 0.0, 100.0);
    double normAvgCPUCoreTemp = std::clamp((avgCPUCoreTemperature - TEMP_MIN)/(TEMP_MAX - TEMP_MIN)*100, 0.0, 100.0);

    double score =
        WEIGHT_RAM*RAMUsagePercent +
        WEIGHT_SWAP*SWAPUsagePercent +
        WEIGHT_CPU_USAGE*systemCPUUsagePercent +
        WEIGHT_CPU_CORE_USAGE*avgCPUCoreUsagePercent +
        WEIGHT_CPU_TEMP*normSystemCPUTemp +
        WEIGHT_CPU_CORE_TEMP*normAvgCPUCoreTemp +
        WEIGHT_CPU_FEQ*systemCPUFreqPercent;
    qDebug() << systemCPUUsagePercent << systemCPUFreqPercent << normSystemCPUTemp
             << avgCPUCoreUsagePercent << normAvgCPUCoreTemp
             << RAMUsagePercent << SWAPUsagePercent
             << "Score:" << score;
    if(score >= OVERLOADING)
        return (int)LoadLevel::STATE_OVERLOADED;
    else if(score >= WARNING)
        return (int)LoadLevel::STATE_WARNING;
    return (int)LoadLevel::STATE_NORMAL;

}
