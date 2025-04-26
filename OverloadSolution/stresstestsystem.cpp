#include "stresstestsystem.h"
#include "../DeviceStats/SystemStats/cpucore.h"
#include "../DeviceStats/SystemStats/systemmem.h"
#include "../utils/processcommand.h"
#include <QJsonDocument>
#include <QDebug>

#define HIGHEST_LEVEL_MEM_TO_STRESS 0.8
#define CONVERT_MB_TO_GB 1024

StressTestSystem::StressTestSystem(QObject *parent)
    : QObject(parent), ExecuteStressTestSystemCommand()
{
    numberOfTaskToRun = 2;
    MEMUsage = 1;
    numberOfCore = 1;
    timeout = 1;
}

void StressTestSystem::setup(int numberOfTaskToRun, float MEMUsagePercent,int numberOfCore,
                             float timeout)
{
    createNumberOfTaskToRun(numberOfTaskToRun);
    setupMEMUsagePercent(MEMUsagePercent);
    setupNumberOfCore(numberOfCore);
    setupTimeout(timeout);
}

void StressTestSystem::createNumberOfTaskToRun(int numberOfTaskToRun)
{
    this->numberOfTaskToRun = numberOfTaskToRun;
}

void StressTestSystem::setupMEMUsagePercent(float MEMUsagePercent)
{
    if (SystemMEM::maxRAMSystem + SystemMEM::maxSWAPMEMSystem <= 0) {
        qDebug() << "Oh, looks like the device doesn't have MEM stats implemented yet";
        return;
    }
    if((MEMUsagePercent < 0) || (MEMUsagePercent > 100)) {
        qDebug() << "Please, You can't set MEM lower 0% or over 100%";
        return;
    }
    const float maxMEM = (SystemMEM::maxRAMSystem + SystemMEM::maxSWAPMEMSystem)*HIGHEST_LEVEL_MEM_TO_STRESS/CONVERT_MB_TO_GB;
    this->MEMUsage = maxMEM*MEMUsagePercent/100.0;
    this->MEMUsage /= numberOfTaskToRun;
}

void StressTestSystem::setupNumberOfCore(int numberOfCore)
{
    if(numberOfCore > CPUCore::numberOfCore) {
        qDebug() << "Oh, looks like the device doesn't have CPU stats implemented yet";
        return;
    }
    if((numberOfCore < 0) || (numberOfCore > CPUCore::numberOfCore)) {
        qDebug() << "Please, set number of cores use to test range of from [0," << CPUCore::numberOfCore << "]";
        return;
    }
    this->numberOfCore = numberOfCore;
}

void StressTestSystem::setupTimeout(float timeout)
{
    // in seconds
    this->timeout = timeout;
}

void StressTestSystem::start(const QJsonObject &obj)
{
    qDebug() << "Start Stress";
    extraStressParam(obj);
    run();
}

void StressTestSystem::extraStressParam(const QJsonObject &obj)
{
    int numbeOfTaskToRun = obj["numberOfTaskToRun"].toInt();
    float MEMUsagePercent = obj["MEMUsagePercent"].toDouble();
    int numberOfCore = obj["numberOfCore"].toInt();
    float timeout = obj["timeout"].toDouble();
    setup(numbeOfTaskToRun, MEMUsagePercent, numberOfCore, timeout);
}

void StressTestSystem::run()
{
    qDebug() << "Run Stress";
    QString command = getStressTestCommand(numberOfTaskToRun, MEMUsage, numberOfCore,  timeout);
    ProcessCommand::execute(command);
}

void StressTestSystem::stop()
{
    QString command = getStopStressTestCommand();
    ProcessCommand::execute(command);
}

