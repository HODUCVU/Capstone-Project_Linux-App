#ifndef TESTING_H
#define TESTING_H

#include "OverloadSolution/terminateprocesses.h"
#include "DeviceStats/SystemStats/systemstats.h"
#include "DeviceStats/ProcessesStats/processesstats.h"
#include <QObject>
#include <QTimer>

class Testing : public QObject
{
    Q_OBJECT
private:
    QTimer timer;
private:
    SystemStats systemStats;
    ProcessesStats processes;
    TerminateProcesses terminateCommand;
public:
    explicit Testing(QObject *parent = nullptr);
public:
    void start();
// System Stats
public:
    void testingGeneralCPUStats();
    void testingCoreCPUStats();
    void testingMEMStats();
private:
    void printGeneralCPUStats(CPUGeneral general);
    void printCoreCPUStats(CPUCore core);
    void printMEMSats(SystemMEM MEM);
// Processes Stats
public:
    void testingProcessesStats();
private:
    void printProcessesStats();
// Terminate Processes
public:
    void testingTerminateProcesses();
private:

};

#endif // TESTING_H
