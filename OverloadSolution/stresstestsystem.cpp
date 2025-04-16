#include "stresstestsystem.h"
#include "../DeviceStats/SystemStats/cpucore.h"
#include "../DeviceStats/SystemStats/systemmem.h"
#include "../utils/processcommand.h"
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
    thread = nullptr;
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

void StressTestSystem::setupNumberOfCore(float numberOfCore)
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

void StressTestSystem::start()
{
    if(thread) return;
    thread = new QThread();
    this->moveToThread(thread);
    connect(thread, &QThread::started, this, &StressTestSystem::run);
    connect(this, &StressTestSystem::finished, thread, &QThread::quit);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    thread->start();
}

void StressTestSystem::run()
{
    QString command = getStressTestCommand(numberOfTaskToRun, MEMUsage, numberOfCore,  timeout);
    ProcessCommand::execute(command);
    emit finished();
}

void StressTestSystem::stop()
{
    QString command = getStopStressTestCommand();
    ProcessCommand::execute(command);
    if (thread && thread->isRunning()) {
        thread->quit();
        thread->wait();
        thread = nullptr;
    }
}

