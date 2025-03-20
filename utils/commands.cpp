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
    MEMUtilizationCommand = "free -m | awk 'NR==2 {print $3}'";
    maxMEMSystemCommand = "free -m | awk 'NR==2 {print $2}'";
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
    /*
    > pidstat -druht 1 5
    =>  # Time        UID      TGID       TID    %usr %system  %guest   %wait    %CPU   CPU  minflt/s  majflt/s     VSZ     RSS   %MEM   kB_rd/s   kB_wr/s kB_ccwr/s iodelay  Command
        04:30:55 PM     0        56         -    0.00    0.75    0.00    0.00    0.75     6      0.00      0.00       0       0   0.00     -1.00     -1.00     -1.00       0  ksoftirqd/6
        04:30:55 PM     0         -        56    0.00    0.75    0.00    0.00    0.75     6      0.00      0.00       0       0   0.00     -1.00     -1.00     -1.00       0  |__ksoftirqd/6
        04:30:55 PM     0       193         -    0.00    0.75    0.00    0.00    0.75     4      0.00      0.00       0       0   0.00     -1.00     -1.00     -1.00       0  kworker/4:1H-events_highpri
        04:30:55 PM     0         -       193    0.00    0.75    0.00    0.00    0.75     4      0.00      0.00       0       0   0.00     -1.00     -1.00     -1.00       0  |__kworker/4:1H-events_highpri
        04:30:55 PM     0       359         -    0.00    0.75    0.00    0.00    0.75     6      1.50      0.00  328616  114652   0.72     -1.00     -1.00     -1.00       0  systemd-journal
        04:30:55 PM     0         -       359    0.75    0.75    0.00    0.00    1.50     6      1.50      0.00  328616  114652   0.72     -1.00     -1.00     -1.00       0  |__systemd-journal
        04:30:55 PM  1000      2337         -    0.00    0.75    0.00    0.00    0.75     1      0.00      0.00  136076   20772   0.13      0.00      0.00      0.00       0  pipewire

    >  echo "PID | Name | %CPU | %MEM | Disk R/W | Network Rx/Tx"
       ps -eo pid,comm,%cpu,%mem --sort=-%cpu | head -n 10
       pidstat -druht 1 1 | grep -v "^#" | head -n 10
       sudo iotop -botq | head -n 10
       sudo nethogs -t | head -n 10

    */
    processesInfoCommand = "command";
}
QString ExecuteProcessStatsCommand::getprocessesInfoCommand()
{
    return processesInfoCommand;
}
