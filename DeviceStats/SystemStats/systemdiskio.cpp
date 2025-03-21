#include "systemdiskio.h"
#include "../../utils/processcommand.h"
#include <QDebug>

SystemDiskIO::SystemDiskIO()
    : ExecuteSystemDiskIOCommand()
{
    getDiskTypeFromDevice();
    totalReadGB = 0.0;
    totalWrittenGB = 0.0;
    reading = 0.0;
    writing = 0.0;
}

float SystemDiskIO::getReadingSpeed()
{
    return reading;
}

float SystemDiskIO::getWritingSpeed()
{
    return writing;
}

float SystemDiskIO::getTotalReadGB()
{
    return totalReadGB;
}

float SystemDiskIO::getTotalWrittenGB()
{
    return totalWrittenGB;
}

void SystemDiskIO::getDiskTypeFromDevice()
{
    QString command = getDiskTypeCommand();
    QString output = ProcessCommand::execute(command);
    QStringList disks = output.split("\n");
    this->diskType = !disks.isEmpty() ? disks.first() : "Unknown";
}

void SystemDiskIO::getDiskIOInfoFromDevice()
{
    QString command = getDiskIOInfoCommand(this->diskType);
    QString output = ProcessCommand::execute(command);
    QStringList diskIOValues = output.split(" ");
    extractDiskIOInfo(diskIOValues);
}
void SystemDiskIO::extractDiskIOInfo(QStringList info)
{
    this->reading = info[0].toFloat();
    this->writing = info[1].toFloat();
    this->totalReadGB = info[2].toFloat()/(1024.0*1024);
    this->totalWrittenGB = info[3].toFloat()/(1024.0*1024);
}

