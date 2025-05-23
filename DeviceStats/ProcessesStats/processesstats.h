#ifndef PROCESSESSTATS_H
#define PROCESSESSTATS_H

#include "../../utils/commands.h"
#include "processstats.h"
#include <QVector>
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
    float getProcessesMEMUsageFromDevice(int PID);
};

#endif // PROCESSESSTATS_H
