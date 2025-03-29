#ifndef SYSTEMMEM_H
#define SYSTEMMEM_H

#include "../../utils/commands.h"

class SystemMEM : public ExecuteSystemMEMCommand
{
private:
    float RAMUtilization;
    float SWAPMEMUtilization;
public: // Getter
    float getRAMUtilization();
    float getRAMUtilizationPercent();
    float getSWAPMEMUtilization();
    float getSWAPMEMUtilizationPercent();
public:
    SystemMEM();
    static float maxRAMSystem;
    static float maxSWAPMEMSystem;
    // Get stats from device
    void getMEMUtilizationFromDevice();

private:
    void getMaxMEMSystemFromDevice();
    void extractMEMUtilizationInfo(QStringList info);
    void extractMaxMEMSystemInfo(QStringList info);
};

#endif // SYSTEMMEM_H
