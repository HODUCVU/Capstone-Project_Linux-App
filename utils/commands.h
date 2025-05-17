#ifndef COMMANDS_H
#define COMMANDS_H
#include <QString>

class ExecuteCPUCoreCommand {
protected:
    QString getnumberOfCoreCPUCommand()const;
    QString getCPUUtilizationCommand() const;

    QString getCPUTemperatureCommand() const;
    QString getcoreCPUTemperatureCommand() const;

    QString getCPUFrequencyMaxMinCommand() const;
    QString getCPUFrequencyPercentCommand() const;
    QString getcoreCPUFrequencyCommand() const;
public:
    ExecuteCPUCoreCommand();
};

class ExecuteSystemMEMCommand {
protected:
    QString getMEMUtilizationCommand() const;
    QString getMaxMEMSystemCommand() const;
public:
    ExecuteSystemMEMCommand();
};

class ExecuteProcessStatsCommand {
protected:
    QString getprocessesInfoCommand() const;
public:
    ExecuteProcessStatsCommand();
};

class ExecuteTerminateProcessesCommand {
    // kill theo PName: pkill command
protected:
    QString getTerminateProcessCommand(QString PName) const;
public:
    ExecuteTerminateProcessesCommand();
};
class ExecuteDeviceSpeakerCommand {
protected:
    QString getAlarmCommand(int repeat, float freq, float length) const;
public:
    ExecuteDeviceSpeakerCommand();
};

class ExecuteStressTestSystemCommand {
protected:
    QString getStressTestCommand(int numberOfTask = 2, float MEMUsageGB = 6.5, int numberOfCore = 4, float timeout = 30) const;
    QString getStopStressTestCommand() const;
public:
    ExecuteStressTestSystemCommand();
};
#endif // COMMANDS_H
