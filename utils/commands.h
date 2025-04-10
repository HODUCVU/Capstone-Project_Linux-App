#ifndef COMMANDS_H
#define COMMANDS_H
#include <QString>

class ExecuteInstallLinuxAPICommand{
private:
    QString installCommand;
protected:
    QString getinstallCommand();
public:
    ExecuteInstallLinuxAPICommand();
};

class ExecuteCPUCoreCommand {
private:
    QString numberOfCoreCPUCommand;
    QString CPUUtilizationCommand;

    QString CPUTemperatureCommand;
    QString coreCPUTemperatureCommand;

    QString CPUFrequencyMaxMinCommand;
    QString CPUFrequencyPercentCommand;
    QString coreCPUFrequencyCommand;
protected:
    QString getnumberOfCoreCPUCommand();
    QString getCPUUtilizationCommand();

    QString getCPUTemperatureCommand();
    QString getcoreCPUTemperatureCommand();

    QString getCPUFrequencyMaxMinCommand();
    QString getCPUFrequencyPercentCommand();
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

class ExecuteProcessStatsCommand {
private:
    QString processesInfoCommand;
protected:
    QString getprocessesInfoCommand();
public:
    ExecuteProcessStatsCommand();
};

class ExecuteTerminateProcessesCommand {
    // kill theo PName: pkill command
private:
    QString terminateProcessCommand;
protected:
    QString getTerminateProcessCommand(QString PName);
public:
    ExecuteTerminateProcessesCommand();
};
class ExecuteDeviceSpeakerCommand {
private:
    QString alarmCommand;
protected:
    QString getAlarmCommand(int repeat, float freq, float length);
public:
    ExecuteDeviceSpeakerCommand();
};

class ExecuteStressTestSystemCommand {
private:
    QString stressTestCommand;
    QString stopStressTestCommand;
protected:
    QString getStressTestCommand(int numberOfTask = 2, float MEMUsageGB = 6.5, int numberOfCore = 4, float timeout = 30);
    QString getStopStressTestCommand();
public:
    ExecuteStressTestSystemCommand();
};
#endif // COMMANDS_H
