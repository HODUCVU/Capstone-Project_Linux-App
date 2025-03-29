#include "systemmem.h"
#include "../../utils/processcommand.h"
#include <QDebug>

SystemMEM::SystemMEM()
    : ExecuteSystemMEMCommand()
{
    getMaxMEMSystemFromDevice();
}
float SystemMEM::maxRAMSystem = 0.0;
float SystemMEM::maxSWAPMEMSystem = 0.0;

float SystemMEM::getRAMUtilization()
{
    return RAMUtilization;
}
float SystemMEM::getRAMUtilizationPercent()
{
    return RAMUtilization/maxRAMSystem;
}

float SystemMEM::getSWAPMEMUtilization()
{
    return SWAPMEMUtilization;
}
float SystemMEM::getSWAPMEMUtilizationPercent()
{
    return SWAPMEMUtilization/maxSWAPMEMSystem;
}

void SystemMEM::getMEMUtilizationFromDevice()
{
    QString command = getMEMUtilizationCommand();
    QString output = ProcessCommand::execute(command);
    QStringList info = output.split('\n');
    extractMEMUtilizationInfo(info);
}
void SystemMEM::extractMEMUtilizationInfo(QStringList info) {
    RAMUtilization = info[0].toFloat();
    SWAPMEMUtilization = info[1].toFloat();
}

void SystemMEM::getMaxMEMSystemFromDevice()
{
    QString command = getMaxMEMSystemCommand();
    QString output = ProcessCommand::execute(command);
    QStringList info = output.split("\n");
    extractMaxMEMSystemInfo(info);
}
void SystemMEM::extractMaxMEMSystemInfo(QStringList info)
{
    maxRAMSystem = info[0].toFloat();
    maxSWAPMEMSystem = info[1].toFloat();
}
