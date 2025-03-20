#include "systemmem.h"
#include "../../utils/processcommand.h"
#include <QDebug>

SystemMEM::SystemMEM()
    : ExecuteSystemMEMCommand()
{
    getMaxMEMSystemFromDevice();
}
float SystemMEM::maxMEMSystem = 0.0;

float SystemMEM::getMEMUtilization()
{
    return MEMUtilization;
}

float SystemMEM::getMEMUtilizationPercent()
{
    return MEMUtilization/maxMEMSystem;
}

void SystemMEM::getMEMUtilizationFromDevice()
{
    QString command = getMEMUtilizationCommand();
    QString output = ProcessCommand::execute(command);
    MEMUtilization = output.toFloat();
}

void SystemMEM::getMaxMEMSystemFromDevice()
{
    QString command = getMaxMEMSystemCommand();
    QString output = ProcessCommand::execute(command);
    maxMEMSystem = output.toFloat();
}
