#ifndef STRESSTESTSYSTEM_H
#define STRESSTESTSYSTEM_H

#include  "../utils/commands.h"
#include <QObject>
#include <QThread>

class StressTestSystem : public QObject, ExecuteStressTestSystemCommand
{
    Q_OBJECT
private:
    int numberOfTaskToRun;
    float MEMUsage;
    int numberOfCore;
    float timeout;
    QThread *thread;
public:
    StressTestSystem(QObject *parent = nullptr);
    void setup(int numberOfTaskToRun = 2, float MEMUsagePercent = 1, int numberOfCore = 1,  float timeout = 1);
    void createNumberOfTaskToRun(int numberOfTaskToRun);
    void setupMEMUsagePercent(float MEMUsagePercent);
    void setupNumberOfCore(float numberOfCore);
    void setupTimeout(float timeout);
    void start();
    void stop();
private slots:
    void run();
signals:
    void finished();
};

#endif // STRESSTESTSYSTEM_H
