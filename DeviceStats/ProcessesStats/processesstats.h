#ifndef PROCESSESSTATS_H
#define PROCESSESSTATS_H

#include "../../utils/commands.h"
#include "processstats.h"
#include <QHash>
#include <QObject>
/*
 * Fix query task stats
 * Testing that functions
 * Build Connect to Client function
*/
class ProcessesStats : public QObject, public ExecuteProcessStatsCommand
{
    Q_OBJECT
public:
    QHash<int, ProcessStats> processesStats;
public:
    explicit ProcessesStats(QObject *parent = nullptr);
    ~ProcessesStats();
    void getProcessStatsFromDevice();
private:
    void extractProcessesInfo(QStringList lines);
    // void updateProcessStats(ProcessStats processStats);

public: // unit tests
    void testingProcessesStats();
};

#endif // PROCESSESSTATS_H
