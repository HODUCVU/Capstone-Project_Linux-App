#include "systemstats.h"

SystemStats::SystemStats(QObject *parent)
    : QObject(parent)
{
    CPUStats = SystemCPU();
    MEMStats = SystemMEM();
}
