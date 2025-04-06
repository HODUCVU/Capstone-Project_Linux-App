#include "systemstats.h"

SystemStats::SystemStats()
{
    CPUStats = SystemCPU();
    MEMStats = SystemMEM();
}
