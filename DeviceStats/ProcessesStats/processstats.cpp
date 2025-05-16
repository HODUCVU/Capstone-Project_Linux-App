#include "processstats.h"
#include "../SystemStats/systemmem.h"
#include <QDebug>

ProcessStats::ProcessStats()
{
    PID = 0;
    user = 0;
    PName = "";
    PCPUUsagePercent = 0.0;
    PMEMUsagePercent = 0.0;
    PMENUsageMB = 0.0;
}

ProcessStats::ProcessStats(QString PName, QString user, int PID, float PCPUPercent)
    : PName(PName), user(user), PID(PID), PCPUUsagePercent(PCPUPercent)
{}

ProcessStats::ProcessStats(float PMEMPercent, float PMENUsageMB)
    : PMEMUsagePercent(PMEMPercent), PMENUsageMB(PMENUsageMB)
{}

ProcessStats::ProcessStats(QString PName, QString user, int PID,
                           float PCPUUsagePercent, float PMEMUsagePercent, float PMENUsageMB)
    : PName(PName), user(user), PID(PID),
    PCPUUsagePercent(PCPUUsagePercent), PMEMUsagePercent(PMEMUsagePercent), PMENUsageMB(PMENUsageMB)
{}

int ProcessStats::getPID()
{
    return PID;
}

QString ProcessStats::getPName()
{
    return PName;
}

QString ProcessStats::getUser()
{
    return user;
}

float ProcessStats::getPCPUUsagePercent()
{
    return PCPUUsagePercent;
}

float ProcessStats::getPMEMUsagePercent()
{
    return PMEMUsagePercent;
}

float ProcessStats::getPMEMUsageMB()
{
    return PMENUsageMB;
}

void ProcessStats::print()
{
    qDebug() << PID << "\t"
             << user << "\t"
             << PCPUUsagePercent << "%\t"
             << PMEMUsagePercent << "%\t"
             << PMENUsageMB << "MB\t"
             << PName;
}

