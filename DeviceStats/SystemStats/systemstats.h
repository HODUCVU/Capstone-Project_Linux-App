#ifndef SYSTEMSTATS_H
#define SYSTEMSTATS_H

#include "systemcpu.h"
#include "systemmem.h"

class SystemStats
{
public:
    SystemCPU CPUStats;
    SystemMEM MEMStats;
public:
    SystemStats();
};

#endif // SYSTEMSTATS_H
