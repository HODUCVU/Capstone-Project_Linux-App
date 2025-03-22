#ifndef PROCESSESSTATS_H
#define PROCESSESSTATS_H

#include "../../utils/commands.h"
#include "processstats.h"
#include <QObject>

class ProcessesStats : ExecuteProcessStatsCommand
{
public:
    QHash<QString, ProcessStats> processesStats;
public:
    ProcessesStats();
    void getProcessStatsFromDevice();
private:
    void extractProcessesInfo(QStringList lines);
};

#endif // PROCESSESSTATS_H
