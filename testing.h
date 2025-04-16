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
    int overloadingDetectAdvance(SystemStats &systemStats);
    void processesFilter(ProcessesStats &processesStats);
private:
    QHash<QString, int> readPriority();
    int maxKillCount = 5; // hoặc giá trị mặc định bạn muốn
};

#endif // TESTING_H
