#include "cpugeneral.h"

CPUGeneral::CPUGeneral() {}

float CPUGeneral::getCPUUtilization()
{
    return this->CPUUtilization;
}
float CPUGeneral::getCPUTemperature()
{
    return this->CPUTemperature;
}
float CPUGeneral::getCPUFrequencyPercent()
{
    return this->CPUFrequencyPercent;
}
float CPUGeneral::getCPUFrequency()
{
    float range = (this->CPUFrequencyMax - this->CPUFrequencyMin);
    return this->CPUFrequencyMin + range*this->CPUFrequencyPercent/100;
}
