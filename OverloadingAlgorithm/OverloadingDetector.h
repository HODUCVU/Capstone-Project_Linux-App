#ifndef OVERLOADINGDETECTOR_H
#define OVERLOADINGDETECTOR_H

#include "../DeviceStats/SystemStats/systemstats.h"
#include <QVector>

enum class LoadLevel {
    STATE_NORMAL = 0,
    STATE_WARNING,
    STATE_OVERLOADED
};

struct SystemMetrics {
    double cpuUsage;
    double cpuTemp;
    double cpuFreq;
    double ramUsagePercent;
    double swapUsagePercent;
};

class OverloadingDetector {
    public:
        OverloadingDetector();
        int detect(SystemStats &systemStats);
    private:
        SystemMetrics getMetrics(SystemStats &systemStats);
        bool isCriticalOverloading(double cpuUsage, double memUsage, double normTemp);
        float balancePenalty(QVector<CPUCore> &cores);
        float calCoreImbalance(QVector<CPUCore> &cores);
        void printValidateLoading(SystemMetrics &metrics, double normTemp, float &score);
        int validLoading(float &score);
};

#endif
