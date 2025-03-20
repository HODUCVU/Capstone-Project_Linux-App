#ifndef SYSTEMCPU_H
#define SYSTEMCPU_H
#include "../../utils/commands.h"
#include "cpucore.h"
#include <QObject>

/*
 * Công việc tiếp theo
 * Lấy nhiệt độ -> done
 * và tần số của từng core -> done
 * Test các module này -> done
 * Gộp vào hệ thống -> done
 * Tối ưu thông qua các công việc dưới đây ↓
*/
/*
 * Có thể tại lệnh %, chỉ cần lấy % là được rồi,
 * không cần lấy ID, dù gì thì nó cũng sắp xếp theo thứ tự tăng dần rồi,
 * không cần phải lấy thông tin thừa, làm tăng runtime -> done
*/
/*
 * Có thể kết hợp %,t,f vào 1 command và chạy 1 function?
 * => hạn chế delay do trích xuất thông tin nhiều lần -> được, nhưng như vậy thì code khó bảo trì và khó đọc
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
private:
    void setupCores();
    void getFrequencyMaxMinFromDevice();
    void extractCoresCPUUsageInfo(QStringList lines);
    void extractCoresCPUTemperatureInfo(QStringList lines);
    void extractCoreCPUFrequencyInfo(QStringList lines);

public: // Testing Functions
    void testtingCPUStats();
    void printCPUStats();

    void testtingCoreCPUStats();
    void printCoreCPUStats();
};

#endif // SYSTEMCPU_H
