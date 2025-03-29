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
    QString networkInterfaceTypeCommand;
protected:
    QString getnetworkInterfaceTypeCommand();
    QString getTotalReceivedCommand(QString interface);
    QString getTotalSentCommand(QString interface);
public:
    ExecuteSystemNetworkIOCommand();
};

class ExecuteSystemDiskIOCommand{
private:
    QString DiskTypeCommand;
protected:
    QString getDiskTypeCommand();
    QString getDiskIOInfoCommand(QString diskType);
public:
    ExecuteSystemDiskIOCommand();
};

class ExecuteProcessStatsCommand {
private:
    QString processesInfoCommand;
protected:
    QString getprocessesInfoCommand();
public:
    ExecuteProcessStatsCommand();
};

class ExecuteTerminateProcessesCommand{
    // kill theo PName: pkill command
private:
    QString terminateProcessCommand;
protected:
    QString getTerminateProcessCommand(QString PName);
public:
    ExecuteTerminateProcessesCommand();
};
class ExecuteDeviceSpeakerCommand{};
#endif // COMMANDS_H
