#ifndef PROCESSSTATS_H
#define PROCESSSTATS_H

#include <QString>

class ProcessStats
{
    int PID;
    QString PName;
    QString user;
    float PCPUUsagePercent;
    float PMEMUsagePercent;
    float PMEMUsageMB;
    // float PDiskReading;
    // float PDiskWriting;
public:
    ProcessStats();
    ProcessStats(QString PName, QString user);
    ProcessStats(QString PName, QString user, int PID, float PCPUUsagePercent, float PMEMUsagePercent);
    // ProcessStats &operator=(const ProcessStats &other);
    // Getter
    QString getPName();
    QString getUser();
    int getPID();
    float getPCPUUsagePercent();
    float getPMEMUsagePercent();
    float getPMEMUsageMB();
    // Setter
    void setPCPUUsagePercent(int PCPUUsagePercent);
    void setPMEMUsagePercent(int PMEMUsagePercent);
};

#endif // PROCESSSTATS_H
