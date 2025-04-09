#ifndef SENDERWORKER_H
#define SENDERWORKER_H

#include "../DeviceStats/SystemStats/systemstats.h"
#include "../DeviceStats/ProcessesStats/processesstats.h"
#include <QObject>
#include <QTimer>
#include <QJsonObject>
#include <QString>

class SenderWorker : public QObject
{
    Q_OBJECT
private:
    QTimer *timer;
    QString timestamp;
    // Stats here
    SystemStats systemStats;
    ProcessesStats processesStats;
public:
    explicit SenderWorker(QObject *parent = nullptr);
    ~SenderWorker();
public slots:
    void run();
private slots:
    void collectStats();
signals:
    void sendMessage(const QJsonObject &obj);
private:
    // Timestamp
    void currentDateTime();
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

    void print();
};

#endif // SENDERWORKER_H
