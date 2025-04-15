#ifndef PROCESSSTATS_H
#define PROCESSSTATS_H

#include <QString>

class ProcessStats
{
private:
    int PID;
    QString PName;
    QString user;
    float PCPUUsagePercent;
    float PMEMUsagePercent;
    float PMEMUsageMB;
public:
    ProcessStats();
    ProcessStats(QString PName, QString user);
    ProcessStats(QString PName, QString user, int PID, float PCPUUsagePercent, float PMEMUsagePercent);
    friend class ProcessesStats;
    // Getter
    QString getPName();
    QString getUser();
    int getPID();
    float getPCPUUsagePercent();
    float getPMEMUsagePercent();
    float getPMEMUsageMB();
};

#endif // PROCESSSTATS_H
