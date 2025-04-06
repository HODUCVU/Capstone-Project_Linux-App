#ifndef SENDERWORKER_H
#define SENDERWORKER_H

#include "../DeviceStats/SystemStats/systemstats.h"
#include "../DeviceStats/ProcessesStats/processesstats.h"
#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QJsonObject>

class SenderWorker : public QObject
{
    Q_OBJECT
private:
    QTcpSocket socket;
    QTimer *timer;
    // Stats here
    SystemStats systemStats;
    ProcessesStats processesStats;
public:
    explicit SenderWorker(QObject *parent = nullptr);
public slots:
    void run();
    void collectStats();
private:
    // Collect stats
    void collectSystemStats();
    void collectGeneralCPUStats();
    void collectCoreCPUStats();
    void collectMEMStats();
    void collectProcessesStats();

    void sendStats();
    // Stats to Json Data type
    QJsonObject systemStatsToJson();
    QJsonObject systemGeneralCPUToJson();
    QJsonObject systemCoresCPUToJson();
    QJsonObject systemMEMToJson();

    QJsonObject processesStatsToJson();
};

#endif // SENDERWORKER_H
