#include "commands.h"
// ========================================
ExecuteCPUCoreCommand::ExecuteCPUCoreCommand() {}

QString ExecuteCPUCoreCommand::getnumberOfCoreCPUCommand() const
{
    return "nproc";
}
QString ExecuteCPUCoreCommand::getCPUUtilizationCommand() const
{
    return "mpstat -P ALL 1 1 | awk 'NR>3 && NR<13 {print 100-$NF}'";
}

QString ExecuteCPUCoreCommand::getCPUTemperatureCommand() const
{
    return "sensors | grep 'CPU' | awk '{print $NF}'";
}

QString ExecuteCPUCoreCommand::getcoreCPUTemperatureCommand() const
{
    return "sensors | awk '/Core/ {print $3}'";
}

QString ExecuteCPUCoreCommand::getCPUFrequencyMaxMinCommand() const
{
    return "lscpu | grep 'MHz' | awk 'NR>1 {print $NF}'";
}

QString ExecuteCPUCoreCommand::getCPUFrequencyPercentCommand() const
{
    return "lscpu | grep 'MHz' | awk 'NR==1 {print $NF}'";
}


QString ExecuteCPUCoreCommand::getcoreCPUFrequencyCommand() const
{
    return "cat /sys/devices/system/cpu/cpu*/cpufreq/scaling_cur_freq";
}

// ========================================
ExecuteSystemMEMCommand::ExecuteSystemMEMCommand() {}
QString ExecuteSystemMEMCommand::getMEMUtilizationCommand() const
{
    return "free -m | awk 'NR>=2 {print $3}'";
}

QString ExecuteSystemMEMCommand::getMaxMEMSystemCommand() const
{
    return "free -m | awk 'NR>=2 {print $2}'";
}

// ========================================
ExecuteProcessStatsCommand::ExecuteProcessStatsCommand() {}
QString ExecuteProcessStatsCommand::getprocessesInfoCommand() const
{
    return "ps -eo comm,user,pid,%cpu,%mem |awk 'NR>1'";
}

// ========================================
ExecuteTerminateProcessesCommand::ExecuteTerminateProcessesCommand() {}
QString ExecuteTerminateProcessesCommand::getTerminateProcessCommand(QString PName) const
{
    return "pkill --exact --echo " + PName;
}

// ========================================
ExecuteDeviceSpeakerCommand::ExecuteDeviceSpeakerCommand() {}

QString ExecuteDeviceSpeakerCommand::getAlarmCommand(int repeat, float freq, float length) const
{
    return "softbeep -f " + QString::number(freq) + " -l " + QString::number(length) + " -r " + QString::number(repeat);
}

// ========================================
ExecuteStressTestSystemCommand::ExecuteStressTestSystemCommand() {}

QString ExecuteStressTestSystemCommand::getStressTestCommand(int numberOfTask, float MEMUsageGB, int numberOfCore, float timeout) const
{
    return "stress --vm " + QString::number(numberOfTask) +
           " --vm-bytes " + QString::number(MEMUsageGB) + "G" +
           " --cpu " + QString::number(numberOfCore) +
           " --timeout " + QString::number(timeout);
}

QString ExecuteStressTestSystemCommand::getStopStressTestCommand() const
{
    return "killall stress";
}
