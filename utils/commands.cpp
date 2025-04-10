#include "commands.h"


ExecuteInstallLinuxAPICommand::ExecuteInstallLinuxAPICommand()
{
    installCommand = "apt update && apt install -y qtbase5-dev sysstat lm-sensors procps";
}

QString ExecuteInstallLinuxAPICommand::getinstallCommand()
{
    return installCommand;
}

// ========================================
ExecuteCPUCoreCommand::ExecuteCPUCoreCommand()
{
    numberOfCoreCPUCommand = "nproc";
    CPUUtilizationCommand = "mpstat -P ALL 1 1 | awk 'NR>3 && NR<13 {print $3,100-$NF}'";

    CPUTemperatureCommand = "sensors | grep 'CPU' | awk '{print $NF}'";
    coreCPUTemperatureCommand = "sensors | awk '/Core/ {print $3}'";

    CPUFrequencyMaxMinCommand = "lscpu | grep 'MHz' | awk 'NR>1 {print $NF}'";
    CPUFrequencyPercentCommand = "lscpu | grep 'MHz' | awk 'NR==1 {print $NF}'";
    coreCPUFrequencyCommand = "cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_cur_freq";
}
QString ExecuteCPUCoreCommand::getCPUUtilizationCommand()
{
    return CPUUtilizationCommand;
}

QString ExecuteCPUCoreCommand::getCPUTemperatureCommand()
{
    return CPUTemperatureCommand;
}

QString ExecuteCPUCoreCommand::getCPUFrequencyPercentCommand()
{
    return CPUFrequencyPercentCommand;
}

QString ExecuteCPUCoreCommand::getCPUFrequencyMaxMinCommand()
{
    return CPUFrequencyMaxMinCommand;
}

QString ExecuteCPUCoreCommand::getnumberOfCoreCPUCommand()
{
    return numberOfCoreCPUCommand;
}

QString ExecuteCPUCoreCommand::getcoreCPUTemperatureCommand()
{
    return coreCPUTemperatureCommand;
}
QString ExecuteCPUCoreCommand::getcoreCPUFrequencyCommand()
{
    return coreCPUFrequencyCommand;
}

// ========================================
/*
    > free -m
            total        used        free      shared  buff/cache   available
    Mem:    15648        3193        9018         611        4381       12455
    Swap:   4095           0        4095
    > free -m | awk 'NR==2 {print $2, $3}'
            15648 3081
*/
ExecuteSystemMEMCommand::ExecuteSystemMEMCommand()
{
    MEMUtilizationCommand = "free -m | awk 'NR>=2 {print $3}'";
    maxMEMSystemCommand = "free -m | awk 'NR>=2 {print $2}'";
}
QString ExecuteSystemMEMCommand::getMEMUtilizationCommand()
{
    return MEMUtilizationCommand;
}

QString ExecuteSystemMEMCommand::getMaxMEMSystemCommand()
{
    return maxMEMSystemCommand;
}

// ========================================
ExecuteProcessStatsCommand::ExecuteProcessStatsCommand()
{
   processesInfoCommand = "ps -eo comm,user,pid,%cpu,%mem |awk 'NR>1'";
}
QString ExecuteProcessStatsCommand::getprocessesInfoCommand()
{
    return processesInfoCommand;
}

// ========================================
ExecuteTerminateProcessesCommand::ExecuteTerminateProcessesCommand()
{
    terminateProcessCommand = "pkill --exact --echo ";
}
QString ExecuteTerminateProcessesCommand::getTerminateProcessCommand(QString PName)
{
    return terminateProcessCommand + PName;
}

// ========================================
ExecuteDeviceSpeakerCommand::ExecuteDeviceSpeakerCommand()
{
    alarmCommand = "softbeep";
}

QString ExecuteDeviceSpeakerCommand::getAlarmCommand(int repeat, float freq, float length)
{
    return alarmCommand + " -f " + QString::number(freq) + " -l " + QString::number(length) + " -r " + QString::number(repeat);
}

// ========================================
ExecuteStressTestSystemCommand::ExecuteStressTestSystemCommand()
{
    stressTestCommand = "stress";
    stopStressTestCommand = "killall stress";
}

QString ExecuteStressTestSystemCommand::getStressTestCommand(int numberOfTask, float MEMUsageGB, int numberOfCore, float timeout)
{
    return stressTestCommand +
           " --vm " + QString::number(numberOfTask) +
           " --vm-bytes " + QString::number(MEMUsageGB) + "G" +
           " --cpu " + QString::number(numberOfCore) +
           " --timeout " + QString::number(timeout);
}

QString ExecuteStressTestSystemCommand::getStopStressTestCommand()
{
    return stopStressTestCommand;
}
