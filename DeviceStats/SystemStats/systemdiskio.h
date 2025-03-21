#ifndef SYSTEMDISKIO_H
#define SYSTEMDISKIO_H

#include "../../utils/commands.h"

class SystemDiskIO : public ExecuteSystemDiskIOCommand
{
private:
    QString diskType;
    float reading;
    float writing;
    float totalReadGB;
    float totalWrittenGB;
public:
    SystemDiskIO();
    // Getter
    float getReadingSpeed();
    float getWritingSpeed();
    float getTotalReadGB();
    float getTotalWrittenGB();

    void getDiskIOInfoFromDevice();
private:
    void getDiskTypeFromDevice();
    void extractDiskIOInfo(QStringList info);
};

#endif // SYSTEMDISKIO_H
