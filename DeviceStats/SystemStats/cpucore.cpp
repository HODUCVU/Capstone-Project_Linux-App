#include "cpucore.h"

CPUCore::CPUCore() {
    coreID = 0;
    coreCPUUtilization = 0.0;
    coreTemperature = 0.0;
    coreFrequency = 0.0;
}

CPUCore::CPUCore(int coreID) : coreID(coreID){}

CPUCore::CPUCore(int coreID, float coreCPUUtilization, float coreTemperature, float coreFrequency)
{
    this->coreID = coreID;
    this->coreCPUUtilization = coreCPUUtilization;
    this->coreTemperature = coreTemperature;
    this->coreFrequency = coreFrequency;
}

int CPUCore::numberOfCore = 1;

int CPUCore::getCoreID()
{
    return this->coreID;
}

float CPUCore::getCoreCPUUtilization()
{
    return this->coreCPUUtilization;
}

float CPUCore::getCoreTemperature()
{
    return this->coreTemperature;
}

float CPUCore::getCoreFrequency()
{
    return this->coreFrequency;
}
