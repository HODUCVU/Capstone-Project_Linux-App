#ifndef COMMANDS_H
#define COMMANDS_H
#include <QString>

class ExecuteCPUCoreCommand {
private:
    QString CPUUtilizationCommand;
    QString CPUTemperatureCommand;
    QString CPUFrequencyMaxMinCommand;
    QString CPUFrequencyPercentCommand;

    QString numberOfCoreCPUCommand;
    QString coreCPUUtilizationCommand;
    QString coreCPUTemperatureCommand;
    QString coreCPUFrequencyCommand;

protected:
    QString getCPUUtilizationCommand();
    QString getCPUTemperatureCommand();
    QString getCPUFrequencyMaxMinCommand();
    QString getCPUFrequencyPercentCommand();

    QString getnumberOfCoreCPUCommand();
    QString getcoreCPUUtilizationCommand();
    QString getcoreCPUTemperatureCommand();
    QString getcoreCPUFrequencyCommand();
public:
    ExecuteCPUCoreCommand();
};

class ExecuteSystemMEMCommand {
private:
    QString MEMUtilizationCommand;
    QString maxMEMSystemCommand;
protected:
    QString getMEMUtilizationCommand();
    QString getMaxMEMSystemCommand();
public:
    ExecuteSystemMEMCommand();
};

class ExecuteSystemNetworkIOCommand {
private:
    QString readAndwriteSpeedInfoCommand;
    QString bandwidthInfoCommand;
protected:
    QString getreadAndwriteSpeedInfoCommand();
    QString getbandwidthInfoCommand();
public:
    ExecuteSystemNetworkIOCommand();
    // virtual void getNetworkReadAndWriteSpeedFromDevice() = 0;
    // virtual void getBandwidthFromDevice() = 0;
};

class ExecuteSystemDiskIOCommand{
private:
    QString readAndwriteSpeedInfoCommand;
    QString totalDiskIOCommand;
protected:
    QString getreadAndwriteSpeedInfoCommand();
    QString gettotalDiskIOCommand();
public:
    ExecuteSystemDiskIOCommand();
    // virtual void getDiskReadAndWriteSpeedFomDevice() = 0;
    // virtual void getTotalReadAndTotalWriteFromDevice() = 0;
};

class ExecuteProcessStatsCommand {
private:
    QString processesInfoCommand;
protected:
    QString getprocessesInfoCommand();
public:
    ExecuteProcessStatsCommand();
    // virtual void getProcessesStatsFromDevice() = 0; // pass processStats[]
};

class ExecuteTerminateProcessesCommand{};
class ExecuteDeviceSpeakerCommand{};
#endif // COMMANDS_H
