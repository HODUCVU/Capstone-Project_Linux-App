#ifndef CPUCORE_H
#define CPUCORE_H

class CPUCore
{
public:
    static int numberOfCore;
private:
    int coreID;
    float coreCPUUtilization;
    float coreTemperature;
    float coreFrequency;
public:
    CPUCore();
    CPUCore(int coreID);
    CPUCore(int coreID, float coreCPUUtilization, float coreTemperature, float coreFrequency);
    friend class SystemCPU;
// Getter
    int getCoreID();
    float getCoreCPUUilization();
    float getCoreTemperature();
    float getCoreFrequency();
};

#endif // CPUCORE_H
