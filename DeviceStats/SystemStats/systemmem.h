#ifndef SYSTEMMEM_H
#define SYSTEMMEM_H

#include "../../utils/commands.h"

class SystemMEM : public ExecuteSystemMEMCommand
{
private:
    float MEMUtilization;
public: // Getter
    float getMEMUtilization();

public:
    SystemMEM();
    static float maxMEMSystem;
    float getMEMUtilizationPercent();

    // Get stats from device
    void getMEMUtilizationFromDevice();

private:
    void getMaxMEMSystemFromDevice();
};

#endif // SYSTEMMEM_H
