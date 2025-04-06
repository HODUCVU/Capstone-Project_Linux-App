#ifndef SYSTEMMEM_H
#define SYSTEMMEM_H

#include "../../utils/commands.h"
#include <QStringList>

class SystemMEM : public ExecuteSystemMEMCommand
{
public:
    static float maxRAMSystem;
    static float maxSWAPMEMSystem;
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
    void getMEMUtilizationFromDevice();
private:
    void extractMEMUtilizationInfo(QStringList info);
    void getMaxMEMSystemFromDevice();
    void extractMaxMEMSystemInfo(QStringList info);
};

#endif // SYSTEMMEM_H
