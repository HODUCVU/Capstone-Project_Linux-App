#ifndef PROCESSESSTATS_H
#define PROCESSESSTATS_H

#include "../../utils/commands.h"
#include "processstats.h"
#include <QVector>
/*
 * Fix query task stats
 * Testing that functions
 * Build Connect to Client function
*/
class ProcessesStats : public ExecuteProcessStatsCommand
{
public:
    QVector<ProcessStats> processes;
public:
    ProcessesStats();
    ~ProcessesStats();
    void getProcessStatsFromDevice();
private:
    void extractProcessesInfo(QStringList &lines);
    // void extractCPUInfo(QString &line, int idx);
    // void extractMEMInfo(QString &line, int idx);
    // QString whoami(int UID);
};

#endif // PROCESSESSTATS_H
