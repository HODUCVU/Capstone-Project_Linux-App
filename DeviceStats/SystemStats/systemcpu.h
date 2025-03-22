#ifndef SYSTEMCPU_H
#define SYSTEMCPU_H
#include "../../utils/commands.h"
#include "cpucore.h"
#include <QObject>
/*
 * Tối ưu thông qua các công việc dưới đây ↓
 * Có thể kết hợp %,t,f vào 1 command và chạy 1 function?
 * => hạn chế delay do trích xuất thông tin nhiều lần -> được, nhưng như vậy thì code khó bảo trì và khó đọc
*/
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
