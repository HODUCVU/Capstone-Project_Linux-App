#ifndef STRESSTESTSYSTEM_H
#define STRESSTESTSYSTEM_H

#include  "../utils/commands.h"
#include <QObject>
#include <QJsonObject>

class StressTestSystem : public QObject, ExecuteStressTestSystemCommand
{
    Q_OBJECT
private:
    int numberOfTaskToRun;
    float MEMUsage;
    int numberOfCore;
    float timeout;
    // QThread *thread;
public:
    StressTestSystem(QObject *parent = nullptr);
    void setup(int numberOfTaskToRun = 2, float MEMUsagePercent = 1, int numberOfCore = 1,  float timeout = 1);
    void start(const QJsonObject &obj);
    void stop();
public slots:
// private slots:
private:
    void run();
    void extraStressParam(const QJsonObject &obj);
    void createNumberOfTaskToRun(int numberOfTaskToRun);
    void setupMEMUsagePercent(float MEMUsagePercent);
    void setupNumberOfCore(int numberOfCore);
    void setupTimeout(float timeout);
// signals:
    // void finished();
};
#endif // STRESSTESTSYSTEM_H
