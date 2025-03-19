#ifndef CPUCORE_H
#define CPUCORE_H
#include <QObject>
class CPUCore
{
private:
    int coreID;
    float coreCPUUtilization;
    float coreTemperature;
    float coreFrequency;
public:
    static int numberOfCore;
    CPUCore();
    CPUCore(int coreID);
    CPUCore(int coreID, float coreCPUUtilization, float coreTemperature, float coreFrequency);
public: // Getter and Setter
    int getCoreID();

    float getCoreCPUUilization();
    void setCoreCPUUtilization(float coreCPUUtilization);

    float getCoreTemperature();
    void setCoreTemperature(float coreTemperature);

    float getCoreFrequency();
    void setCoreFrequency(float coreFrequency);
};

#endif // CPUCORE_H
