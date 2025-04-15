#ifndef TESTING_H
#define TESTING_H

#include "DeviceStats/SystemStats/systemstats.h"
#include "DeviceStats/ProcessesStats/processesstats.h"
#include <QObject>
#include <QHash>

enum class LoadLevel {
    STATE_NORMAL = 0,
    STATE_WARNING,
    STATE_OVERLOADED
};

class Testing : public QObject
{
    Q_OBJECT
public:
    explicit Testing(QObject *parent = nullptr);
    // void overloadingDetectSimple(SystemStats &systemStats);
    int overloadingDetectAdvance(SystemStats &systemStats);
    void processesFilter(ProcessesStats processesStats);
private:
    // void processesFilterRootProcess(QStringList &PNames, ProcessesStats &processesStats);
    // void processesFilterWhileList(QStringList &PNames);
    // void processesFilterTaskToKill(QStringList &PNames, ProcessesStats &processesStats);
    QHash<QString, int> readPriority();
};

#endif // TESTING_H
