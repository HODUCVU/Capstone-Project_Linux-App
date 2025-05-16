#ifndef OVERLOADINGHANDLER_H
#define OVERLOADINGHANDLER_H

#include "../DeviceStats/ProcessesStats/processesstats.h"
// #include <QHash>
// #include <QSet>
// #include <QString>
// #include <QVector>

// class OverLoadingHandler {
// private:
//     QSet<QString> PNames;
//     QVector<ProcessStats*> filtered;
// public:
//     QString processesFilter(ProcessesStats &processesStats);
// private:
//     void rootFilter(QVector<ProcessStats> &statsList);
//     void WhileListFilter();
//     QVector<QPair<QString, float>> rankingProcessToKill(QHash<QString, int> &priorityMap);
//     QHash<QString, int> readPriority();
// };
#include <QSet>
#include <QVector>
#include <QHash>
#include <QString>
#include <QPair>

class OverLoadingHandler {
public:
    QString selectProcessToKill(ProcessesStats &processesStats);

private:
    ~OverLoadingHandler();
    void filterNonRootProcesses(QVector<ProcessStats> &statsList);
    void applyWhiteListFilter();
    void loadPriorityTable();
    ProcessStats* findProcessToKill(); // Trả về pointer const tới ProcessStats trong filtered

    QSet<QString> whiteList;
    QHash<QString, int> priorityMap;
    QSet<QString> nameSet;            // Lưu tên process hợp lệ
    QVector<ProcessStats*> filtered;   // Tiến trình đã lọc hợp lệ (bằng pointer)
    int maxPriority;           // Max priority có trong file
};
#endif
