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
    float PMENUsageMB;
public:
    ProcessStats();
    ProcessStats(QString PName, QString user, int PID, float PCPUPercent);
    ProcessStats(float PMEMPercent, float PMENUsageMB);
    ProcessStats(QString PName, QString user, int PID,
                 float PCPUUsagePercent, float PMEMUsagePercent, float PMENUsageMB);
    friend class ProcessesStats;
    // Getter
    QString getPName();
    int getPID();
    QString getUser();
    float getPCPUUsagePercent();
    float getPMEMUsagePercent();
    float getPMEMUsageMB();
    void print();
};

#endif // PROCESSSTATS_H
