#ifndef SYSTEMSTATS_H
#define SYSTEMSTATS_H

#include "systemcpu.h"
#include "systemmem.h"
#include "systemnetworkio.h"
#include <QObject>

class SystemStats : public QObject
{
    Q_OBJECT
public:
    SystemCPU CPUStats;
    SystemMEM MEMStats;
    SystemNetworkIO NetworkIOStats;
public:
    explicit SystemStats(QObject *parent = nullptr);

public: // Unit Tests
    // Testing CPU Stats
    void testingCPUStats();
    void printCPUStats();

    void testingCoreCPUStats();
    void printCoreCPUStats();

    // Testing MEM Stats
    void testingMEMUStats();

    // Testing Network IO Stats
    void testingNetworkIDStats();

};

#endif // SYSTEMSTATS_H
