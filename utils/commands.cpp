#include "commands.h"


ExecuteCPUCoreCommand::ExecuteCPUCoreCommand()
{
    CPUUtilizationCommand = "mpstat -P ALL 1 1 | awk '/all/ {print 100 - $NF}'";
    CPUTemperatureCommand = "sensors | grep 'CPU' | awk '{print $NF}'";
    CPUFrequencyMaxMinCommand = "lscpu | grep 'MHz' | awk 'NR>1 {print $NF}'";
    CPUFrequencyPercentCommand = "lscpu | grep 'MHz' | awk 'NR==1 {print $NF}'";

    numberOfCoreCPUCommand = "nproc";
    coreCPUUtilizationCommand = "mpstat -P ALL 1 1 | awk 'NR>4 && NR<13 {print 100-$NF}'";
    coreCPUTemperatureCommand = "sensors | awk '/Core/ {print $3}'";
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

QString ExecuteCPUCoreCommand::getcoreCPUUtilizationCommand()
{
    return coreCPUUtilizationCommand;
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
ExecuteSystemMEMCommand::ExecuteSystemMEMCommand()
{
    // QString Commands::MEMUsage = "free -m | awk 'NR==2{printf \"%.2f%% (%dMB/%dMB)\", $3*100/$2, $3, $2}'";
    /*
    > free -m
            total        used        free      shared  buff/cache   available
    Mem:    15648        3193        9018         611        4381       12455
    Swap:   4095           0        4095
    > free -m | awk 'NR==2 {print $2, $3}'
            15648 3081
    */
    MEMUtilizationCommand = "free -m | awk 'NR==2 {print $2, $3}'";
}
QString ExecuteSystemMEMCommand::getMEMUtilizationCommand()
{
    return MEMUtilizationCommand;
}
// ========================================
ExecuteSystemNetworkIOCommand::ExecuteSystemNetworkIOCommand()
{
    // QString Commands::NETUsage = "ifstat 1 1 | tail -n 1";
    readAndwriteSpeedInfoCommand = "command";
    bandwidthInfoCommand = "command";
}
QString ExecuteSystemNetworkIOCommand::getreadAndwriteSpeedInfoCommand()
{
    return readAndwriteSpeedInfoCommand;
}
QString ExecuteSystemNetworkIOCommand::getbandwidthInfoCommand()
{
    return bandwidthInfoCommand;
}

// ========================================
ExecuteSystemDiskIOCommand::ExecuteSystemDiskIOCommand()
{
    // QString Commands::DiskIO = "iostat -d 1 1 | awk 'NR==4 {print $3 \" KB/s Read, \" $4 \" KB/s Write\"}'";
    readAndwriteSpeedInfoCommand = "command";
    totalDiskIOCommand = "command";
}
QString ExecuteSystemDiskIOCommand::getreadAndwriteSpeedInfoCommand()
{
    return readAndwriteSpeedInfoCommand;
}
QString ExecuteSystemDiskIOCommand::gettotalDiskIOCommand()
{
    return totalDiskIOCommand;
}
// ========================================
ExecuteProcessStatsCommand::ExecuteProcessStatsCommand()
{
    // QString Commands::ProcessStats = "ps -eo pid,comm,%cpu,%mem,rss --sort=-%cpu | awk '$4>0'";
    // ps -eo pid,comm,%cpu --sort=-%cpu | awk -v cores=$(nproc) '{if (NR>1) printf "%d %s %.2f\n", $1, $2, $3/cores}'
    processesInfoCommand = "command";
}
QString ExecuteProcessStatsCommand::getprocessesInfoCommand()
{
    return processesInfoCommand;
}
