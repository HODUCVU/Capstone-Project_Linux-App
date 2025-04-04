#ifndef PROCESSESSTATS_H
#define PROCESSESSTATS_H

#include "../../utils/commands.h"
#include "processstats.h"
#include <QObject>
#include <QVector>
/*
 * Fix query task stats
 * Testing that functions
 * Build Connect to Client function
*/
class ProcessesStats : public QObject, public ExecuteProcessStatsCommand
{
    Q_OBJECT
public:
    QVector<ProcessStats> processes;
public:
    explicit ProcessesStats(QObject *parent = nullptr);
    ~ProcessesStats();
    void getProcessStatsFromDevice();
private:
    void extractProcessesInfo(QStringList lines);

};

#endif // PROCESSESSTATS_H
