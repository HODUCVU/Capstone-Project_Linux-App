#ifndef SYSTEMCPU_H
#define SYSTEMCPU_H
#include "../../utils/commands.h"
#include "cpucore.h"
#include <QObject>

/*
 * Công việc tiếp theo
 * Lấy nhiệt độ và tần số của từng core
 * Test các module này
 * Gộp vào hệ thống
 * Tối ưu thông qua các công việc dưới đây ↓
*/
/*
 * Có thể tại lệnh %, chỉ cần lấy % là được rồi,
 * không cần lấy ID, dù gì thì nó cũng sắp xếp theo thứ tự tăng dần rồi,
 * không cần phải lấy thông tin thừa, làm tăng runtime
*/
/*
 * Có thể kết hợp %,t,f vào 1 command và chạy 1 function?
 * => hạn chế delay do trích xuất thông tin nhiều lần
*/
class SystemCPU : public QObject, public ExecuteCPUCoreCommand
{
    Q_OBJECT
public:
    QVector<CPUCore> cores;
    float CPUUtilization;
    // should I put timer here?
public:
    explicit SystemCPU(QObject *parent = nullptr);
    ~SystemCPU();
    float getCPUUtilization();

    void getNumberOfCoreCPUFromDevice();
    void getCPUUtilizationStatsFromDevice();

    void getCoresCPUUtilizationStatsFromDevice();
    void getCoresTemperatureStatsFromDevice();
    void getCoresFrequencyStatsFromDevice();
private:
    void setupCores();
    void extractCoresCPUUsageInfo(QStringList lines);
    void extractCoresTemperatureInfo(QStringList lines);
};

#endif // SYSTEMCPU_H
