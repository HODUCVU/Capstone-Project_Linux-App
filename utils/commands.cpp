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
    /*
     *  Đang dùng wifỉ: wlp0s20f3
     *  Đang dùng ethernet: enp0s31f6@
     *  ip link show | grep "state UP"
     *  -> 3: wlp0s20f3: <BROADCAST,MULTICAST,UP,LOWER_UP>
     *      mtu 1500 qdisc noqueue state UP mode DORMANT group default qlen 1000
     *  -> Đang dùng wlp0s20f3
    */
    networkInterfaceTypeCommand = "ip link show | grep 'state UP' | awk -F: '{print $2}' | tr -d ' '";
}
QString ExecuteSystemNetworkIOCommand::getnetworkInterfaceTypeCommand()
{
    return networkInterfaceTypeCommand;
}

QString ExecuteSystemNetworkIOCommand::getTotalReceivedCommand(QString interface)
{
    return "cat /sys/class/net/" + interface + "/statistics/rx_bytes";
}

QString ExecuteSystemNetworkIOCommand::getTotalSentCommand(QString interface)
{
    return "cat /sys/class/net/" + interface + "/statistics/tx_bytes";
}

// ========================================
ExecuteSystemDiskIOCommand::ExecuteSystemDiskIOCommand()
{
    // QString Commands::DiskIO = "iostat -d 1 1 | awk '{print $3 \" KB/s Read, \" $4 \" KB/s Write\"}'";
    // Có nhiều loại disk, vì vậy cần kiểm tra loại disk để lấy thông tin chính xác
    DiskTypeCommand = "lsblk -d -o NAME,TYPE | grep disk | awk '{print $1}'";
}
QString ExecuteSystemDiskIOCommand::getDiskTypeCommand()
{
    return DiskTypeCommand;
}

QString ExecuteSystemDiskIOCommand::getDiskIOInfoCommand(QString diskType)
{
    return "iostat -d 1 1 | grep " + diskType +" | awk '{print $3, $4, $6, $7}'";
}

// ========================================
ExecuteProcessStatsCommand::ExecuteProcessStatsCommand()
{
    /*
    // QString Commands::ProcessStats = "ps -eo pid,comm,%cpu,%mem,rss --sort=-%cpu | awk '$4>0'";
    > ps -eo pid,comm,%cpu --sort=-%cpu | awk -v cores=$(nproc) '{if (NR>1) printf "%d %s %.2f\n", $1, $2, $3/cores}'
    > pidstat -druht 1 1
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

    > ps -eo pid,comm,%cpu,%mem --sort=%cpu | awk 'NR>1 {print $1,$2,$3,$4}
    > ps -eo user,pid,comm,%cpu,%mem --sort=-%cpu | grep $(whoami)

    >  pidstat -druh 1 1 | awk 'NR>3 {
                           cmd = $NF;
                           uid[cmd] = $3;  # Lấy UID của tiến trình
                           if (!(cmd in pid)) pid[cmd] = $4;  # Lấy PID chính (chỉ lấy lần đầu)

                           cpu[cmd] += $9;
                           mem[cmd] += $15;
                           rd[cmd] += $16;
                           wr[cmd] += $17;
                       }
                       END {
                           printf "%-10s %-20s %-10s %-10s %-10s %-10s %-10s\n", "UID", "Command", "PID", "%CPU", "%MEM", "kB_rd/s", "kB_wr/s";
                           for (cmd in cpu) {
                               printf "%-10s %-20s %-10s %-10.2f %-10.2f %-10.2f %-10.2f\n", uid[cmd], cmd, pid[cmd], cpu[cmd], mem[cmd], rd[cmd], wr[cmd];
                           }
                       }'

    */
    processesInfoCommand = "ps -eo comm,user,pid,%cpu,%mem --sort=-%cpu | awk 'NR>1'";
}
QString ExecuteProcessStatsCommand::getprocessesInfoCommand()
{
    return processesInfoCommand;
}

QString ExecuteProcessStatsCommand::getprocessesDiskIOCommand(int PID)
{
    return "";
}
