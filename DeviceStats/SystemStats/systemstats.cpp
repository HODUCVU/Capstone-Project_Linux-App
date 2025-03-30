#include "systemstats.h"
#include <QDebug>

SystemStats::SystemStats(QObject *parent)
    : QObject(parent)
{
    CPUStats = SystemCPU();
    MEMStats = SystemMEM();
}
