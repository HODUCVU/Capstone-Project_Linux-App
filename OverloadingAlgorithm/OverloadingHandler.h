#ifndef OVERLOADINGHANDLER_H
#define OVERLOADINGHANDLER_H

#include "../DeviceStats/ProcessesStats/processesstats.h"
#include <QHash>
#include <QSet>
#include <QString>
#include <QVector>

class OverLoadingHandler {
private:
    QSet<QString> PNames;
    QVector<ProcessStats*> filtered;
public:
    QString processesFilter(ProcessesStats &processesStats);
private:
    void rootFilter(QVector<ProcessStats> &statsList);
    void WhileListFilter();
    QVector<QPair<QString, float>> rankingProcessToKill(QHash<QString, int> &priorityMap);
    QHash<QString, int> readPriority();
};
#endif
