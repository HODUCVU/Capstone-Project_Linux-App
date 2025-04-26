#include "OverloadingDetector.h"
#include <QDebug>

#define OVERLOADING 50
#define WARNING 45

// weights
#define WEIGHT_RAM 0.35
#define WEIGHT_SWAP 0.25
#define WEIGHT_CPU 0.25
#define WEIGHT_TEMP 0.10
#define WEIGHT_FREQ 0.05

#define TEMP_MIN 40
#define TEMP_MAX 90

// Critical thresholds
#define CRITICAL_CPU_THRESHOULD 95
#define CRITICAL_MEM_THRESHOULD 190
#define CRITICAL_TEMP_THRESHOULD 85

OverloadingDetector::OverloadingDetector()
{}

int OverloadingDetector::detect(SystemStats &systemStats)
{
    SystemMetrics metrics = getMetrics(systemStats);
    double normTemp = std::clamp((metrics.cpuTemp - TEMP_MIN) / (TEMP_MAX - TEMP_MIN)*100, 0.0, 100.0);

    if(isCriticalOverloading(metrics.cpuUsage, metrics.ramUsagePercent + metrics.swapUsagePercent, normTemp)) {
        qDebug() << "Critical condition detected!";
        qDebug() << "CPU:" << metrics.cpuUsage 
                 << "RAM:" <<  metrics.ramUsagePercent
                 << "SWAP:" << metrics.swapUsagePercent
                 << "Temp:" << normTemp;
        return (int)LoadLevel::STATE_OVERLOADED;
    }
    float score =
        WEIGHT_RAM * metrics.ramUsagePercent +
        WEIGHT_SWAP * metrics.swapUsagePercent +
        WEIGHT_CPU * metrics.cpuUsage +
        WEIGHT_TEMP * normTemp +
        WEIGHT_FREQ * metrics.cpuFreq;
    score += balancePenalty(systemStats.CPUStats.cores);
    printValidateLoading(metrics, normTemp, score);

    return validLoading(score);
}

SystemMetrics OverloadingDetector::getMetrics(SystemStats &systemStats) {
    SystemMetrics metrics;
    metrics.cpuUsage = systemStats.CPUStats.general.getCPUUtilization();
    metrics.cpuTemp = systemStats.CPUStats.general.getCPUTemperature();
    metrics.cpuFreq = systemStats.CPUStats.general.getCPUFrequencyPercent();
    metrics.ramUsagePercent = systemStats.MEMStats.getRAMUtilizationPercent();
    metrics.swapUsagePercent = systemStats.MEMStats.getSWAPMEMUtilizationPercent();
    return metrics;
}

bool OverloadingDetector::isCriticalOverloading(double cpuUsage, double memUsage, double normTemp)
{
    return cpuUsage >= CRITICAL_CPU_THRESHOULD || memUsage >= CRITICAL_MEM_THRESHOULD || normTemp >= CRITICAL_TEMP_THRESHOULD;
}

float OverloadingDetector::balancePenalty(QVector<CPUCore> &cores)
{
    float coreImbalance = calCoreImbalance(cores);
    if(coreImbalance > 0.5) {
        qDebug() << "Core imbalance detected:" << coreImbalance 
                << "Penalty added:" << coreImbalance*10;
        return coreImbalance*10;
    }
    return 0.0;
}

float OverloadingDetector::calCoreImbalance(QVector<CPUCore> &cores)
{
 
    float maxCoreUsage = 0.0;
    float minCoreUsage = 100.0;
    for(auto &core: cores) {
        float coreUsage = core.getCoreCPUUtilization();
        maxCoreUsage = std::max(maxCoreUsage, coreUsage);
        minCoreUsage = std::min(minCoreUsage, coreUsage);
    }   
    float coreImbalance = (maxCoreUsage - minCoreUsage)/100.0;
    return coreImbalance;
}

void OverloadingDetector::printValidateLoading(SystemMetrics &metrics, double normTemp, float &score)
{
    qDebug() << "System Status:"
             << "\n  CPU Usage:" << metrics.cpuUsage << "%"
             << "\n  RAM Usage:" << metrics.ramUsagePercent << "%"
             << "\n  SWAP Usage:" << metrics.swapUsagePercent << "%"
             << "\n  Temperature:" << normTemp << "%"
             << "\n  Final Score:" << score;
}

int OverloadingDetector::validLoading(float &score)
{
    if(score >= OVERLOADING) return (int)LoadLevel::STATE_OVERLOADED;
    else if (score >= WARNING) return (int)LoadLevel::STATE_WARNING;
    return (int)LoadLevel::STATE_NORMAL;
}
