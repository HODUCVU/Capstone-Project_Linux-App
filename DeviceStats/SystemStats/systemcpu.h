#ifndef SYSTEMCPU_H
#define SYSTEMCPU_H
#include "../../utils/commands.h"
#include "cpucore.h"
#include <QObject>

/*
 * Công việc tiếp theo
 * Lấy nhiệt độ -> ok
 * và tần số của từng core -> ok
 * Test các module này
 * Gộp vào hệ thống
 * Tối ưu thông qua các công việc dưới đây ↓
*/
/*
 * Có thể tại lệnh %, chỉ cần lấy % là được rồi, -> được, nhưng như vậy thì code khó bảo trì và khó đọc
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
private:
    float CPUUtilization;
    float CPUTemperature;
    float CPUFrequencyPercent;
    float CPUFrequencyMax;
    float CPUFrequencyMin;
    // should I put timer here?
public: // Getter
    float getCPUUtilization();
    float getCPUTemperature();
    float getCPUFrequencyPercent();
    float getCPUFrequency();
public:
    explicit SystemCPU(QObject *parent = nullptr);
    ~SystemCPU();

    void getCPUUtilizationStatsFromDevice();
    void getCPUTemperatureStatsFromDevice();
    void getCPUFrequencyPercentFromDevice();

    void getNumberOfCoreCPUFromDevice();
    void getCoresCPUUtilizationStatsFromDevice();
    void getCoresTemperatureStatsFromDevice();
    void getCoresFrequencyStatsFromDevice();

    void testtingCPUStats();
private:
    void setupCores();
    void getFrequencyMaxMinFromDevice();
    void extractCoresCPUUsageInfo(QStringList lines);
    void extractCoresCPUTemperatureInfo(QStringList lines);
    void extractCoreCPUFrequencyInfo(QStringList lines);
};

#endif // SYSTEMCPU_H
