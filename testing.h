#ifndef TESTING_H
#define TESTING_H

#include "DeviceStats/SystemStats/systemstats.h"
#include <QObject>

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
private:
    // void overloadingHard();
    // void overloadingSoft();
};

#endif // TESTING_H
