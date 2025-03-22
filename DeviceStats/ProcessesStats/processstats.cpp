#include "processstats.h"
#include "../SystemStats/systemmem.h"

ProcessStats::ProcessStats()
{
    PID = 0;
    PName = "";
    PCPUUsagePercent = 0.0;
    PMEMUsagePercent = 0.0;
    PMEMUsageMB = 0.0;
}

ProcessStats::ProcessStats(QString PName, QString user)
    : PName(PName), user(user)
{}

ProcessStats::ProcessStats(QString PName, QString user, int PID, float PCPUUsagePercent, float PMEMUsagePercent)
    : PName(PName), user(user), PID(PID), PCPUUsagePercent(PCPUUsagePercent), PMEMUsagePercent(PMEMUsagePercent)
{
    this->PMEMUsageMB = PMEMUsagePercent*SystemMEM::maxMEMSystem;
}

int ProcessStats::getPID()
{
    return PID;
}

QString ProcessStats::getPName()
{
    return PName;
}

float ProcessStats::getPCPUUsagePercent()
{
    return PCPUUsagePercent;
}

float ProcessStats::getPMEMUsagePercent()
{
    return PMEMUsagePercent;
}

void ProcessStats::setPID(int id)
{
    this->PID = id;
}

void ProcessStats::setPCPUUsagePercent(int PCPUUsagePercent)
{
    this->PCPUUsagePercent = PCPUUsagePercent;
}
float ProcessStats::getPMEMUsageMB()
{
    return this->PMEMUsageMB;
}
void ProcessStats::setPMEMUsagePercent(int PMEMUsagePercent)
{
    this->PMEMUsagePercent = PMEMUsagePercent;
    this->PMEMUsageMB = PMEMUsagePercent*SystemMEM::maxMEMSystem;
}


