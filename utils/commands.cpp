#include "commands.h"


ExecuteCPUCoreCommand::ExecuteCPUCoreCommand()
{
    // /all/ -> chỉ lấy all, $NF là cái cuối cùng = idle time, 100 - idle time = useage time
    CPUUtilizationCommand = "mpstat -P ALL 1 1 | awk '/all/ {print 100 - $NF}'";
    numberOfCoreCPUCommand = "nproc";
    // coreCPUUtilizationCommand = "mpstat -P ALL 1 1 | awk 'NR>4 && NR<13 {print $3,100-$NF}'";
    coreCPUUtilizationCommand = "mpstat -P ALL 1 1 | awk 'NR>4 && NR<13 {print 100-$NF}'";
    coreTemperatureCommand = "sensors | awk '/Core/ {print $3}'";

    // QString CPUTemperature = "sensors | grep 'CPU' | awk '{print $NF}'";
    // QString Commands::CPUFrequency = "lscpu | grep 'MHz' | awk '{print $NF}'";
    // coreTemperatureCommand = "sensors | grep 'Core' | awk '{print $2 $3}'";
    // coreFrequencyCommand = "awk -F ': ' '/cpu MHz/ {print $2}' /proc/cpuinfo";
}
QString ExecuteCPUCoreCommand::getCPUUtilizationCommand()
{
    return CPUUtilizationCommand;
}

QString ExecuteCPUCoreCommand::getnumberOfCoreCPUCommand()
{
    return numberOfCoreCPUCommand;
}

QString ExecuteCPUCoreCommand::getcoreCPUUtilizationCommand()
{
    return coreCPUUtilizationCommand;
}
QString ExecuteCPUCoreCommand::getcoreTemperatureCommand()
{
    return coreTemperatureCommand;
}
QString ExecuteCPUCoreCommand::getcoreFrequencyCommand()
{
    return coreFrequencyCommand;
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
