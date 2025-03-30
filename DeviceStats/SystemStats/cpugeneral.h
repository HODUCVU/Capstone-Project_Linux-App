#ifndef CPUGENERAL_H
#define CPUGENERAL_H

class CPUGeneral
{
private:
    float CPUUtilization;
    float CPUTemperature;
    float CPUFrequencyPercent;
    float CPUFrequencyMax;
    float CPUFrequencyMin;
public:
    CPUGeneral();
    friend class SystemCPU;
// Getter
    float getCPUUtilization();
    float getCPUTemperature();
    float getCPUFrequencyPercent();
    float getCPUFrequency();
};

#endif // CPUGENERAL_H
