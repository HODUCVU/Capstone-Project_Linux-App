#ifndef STRESSTESTSYSTEM_H
#define STRESSTESTSYSTEM_H

#include  "../utils/commands.h"

class StressTestSystem : ExecuteStressTestSystemCommand
{
private:
    int numberOfTaskToRun;
    float MEMUsage;
    int numberOfCore;
    float timeout;
public:
    StressTestSystem();
    void setup(int numberOfTaskToRun = 2, float MEMUsagePercent = 1, int numberOfCore = 1,  float timeout = 1);
    void createNumberOfTaskToRun(int numberOfTaskToRun);
    void setupMEMUsagePercent(float MEMUsagePercent);
    void setupNumberOfCore(float numberOfCore);
    void setupTimeout(float timeout);
    void start();
    void stop();
};

#endif // STRESSTESTSYSTEM_H
