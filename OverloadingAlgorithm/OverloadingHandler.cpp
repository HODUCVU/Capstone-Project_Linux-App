#include "OverloadingHandler.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

#define DATA_PATH_WHILELIST "../../Datasheet/WhileList.txt"
#define DATA_PATH_PRIORITY "../../Datasheet/PRIORITY.txt"

QString OverLoadingHandler::processesFilter(ProcessesStats &processesStats)
{
    // B1: Lọc tiến trình không phải root (filter 1)
    rootFilter(processesStats.processes);

    // B2: Lọc theo whitelist (filter 2)
    WhileListFilter();

    // B3: Đọc file priority
    QHash<QString, int> priorityMap = readPriority();

    // B4: Tính điểm tiến trình (filter 3)
    QVector<QPair<QString, float>> ranked = rankingProcessToKill(priorityMap);

    // B5: Xếp hạng và lấy top tiến trình => Select Max value instead of sort
    // Sort: O(n^2), Mem: O(n)
    // Max: O(n), Mem: O(1)
    std::sort(ranked.begin(), ranked.end(),
              [](const auto &a, const auto &b) {
                  return a.second > b.second;
              });

    QString toKill = ranked[0].first;
    return toKill; // Send to Linux App
}

void OverLoadingHandler::rootFilter(QVector<ProcessStats> &statsList)
{
    for (auto &process : statsList) {
        if (process.getUser() != "root") {
            QString name = process.getPName();
            PNames.insert(name);
            filtered.append(&process);
        }
    }
}

void OverLoadingHandler::WhileListFilter()
{
    QFile whitelistFile(DATA_PATH_WHILELIST);
    if (whitelistFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&whitelistFile);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty())
                PNames.remove(line);
        }
        whitelistFile.close();
    }
}

QVector<QPair<QString, float>> OverLoadingHandler::rankingProcessToKill(QHash<QString, int> &priorityMap)
{
    QVector<QPair<QString, float>> ranked;
    for (ProcessStats *proc : filtered) {
        QString name = proc->getPName();
        if (!PNames.contains(name))
            continue;

        float cpu = proc->getPCPUUsagePercent();
        float mem = proc->getPMEMUsagePercent();
        int prio = priorityMap.value(name, 2); // mặc định pr = 2 nếu không có

        float score = 0.4f * cpu + 0.4f * mem + 0.2f * prio;
        ranked.append({name, score});
    }
    return ranked;
}

QHash<QString, int> OverLoadingHandler::readPriority()
{
    QHash<QString, int> priorities;
    QFile file(DATA_PATH_PRIORITY);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can't open priority file:" << DATA_PATH_PRIORITY;
        return priorities;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList parts = line.split(":");
        if (parts.size() != 2) continue;

        QString name = parts[0].trimmed();
        int pr = parts[1].toInt();
        priorities[name] = pr;
    }

    file.close();
    return priorities;
}
