#include "OverloadingHandler.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

#define DATA_PATH_WHITELIST "../../Datasheet/WhileList.txt"
#define DATA_PATH_PRIORITY "../../Datasheet/PRIORITY.txt"

QString OverLoadingHandler::selectProcessToKill(ProcessesStats &processesStats)
{
    filtered.clear();
    nameSet.clear();
    whiteList.clear();
    priorityMap.clear();
    maxPriority = 2; // Giá trị ưu tiên mặc định thấp nhất

    // 1. Lọc root
    filterNonRootProcesses(processesStats.processes);

    // 2. Lọc theo whitelist
    applyWhiteListFilter();

    // 3. Đọc file priority
    loadPriorityTable();

    // 4. Tìm process có điểm cao nhất để kill
    ProcessStats* toKill = findProcessToKill();
    if (!toKill)
        return QString(); // Không có gì để kill
    return toKill->getPName();
}

void OverLoadingHandler::filterNonRootProcesses(QVector<ProcessStats> &statsList)
{
    for (auto &proc : statsList) {
        if (proc.getUser() != "root") {
            nameSet.insert(proc.getPName());
            filtered.append(&proc);
        }
    }
}

void OverLoadingHandler::applyWhiteListFilter()
{
    QFile f(DATA_PATH_WHITELIST);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&f);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            whiteList.insert(line);
            nameSet.remove(line); // Loại luôn ra khỏi tập xét
        }
    }
    f.close();
}

void OverLoadingHandler::loadPriorityTable()
{
    QFile f(DATA_PATH_PRIORITY);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can't open priority file:" << DATA_PATH_PRIORITY;
        return;
    }
    QTextStream in(&f);
    while(!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        QStringList parts = line.split(":");
        if (parts.size()!=2) continue;
        QString name = parts[0].trimmed();
        int prio = parts[1].trimmed().toInt();
        if (prio > maxPriority) maxPriority = prio;
        priorityMap[name] = prio;
    }
    f.close();
}

ProcessStats* OverLoadingHandler::findProcessToKill()
{
    // Thuật toán: tìm process score cao nhất
    ProcessStats* maxProc = nullptr;
    float maxScore = -1.0f;

    for (auto* proc : filtered) {
        QString name = proc->getPName();
        if (!nameSet.contains(name)) continue; // Đã bị loại khỏi whitelist

        // Điểm số (CÓ THỂ TUỲ BIẾN):
        float cpu = proc->getPCPUUsagePercent();
        float mem = proc->getPMEMUsagePercent();
        // dùng maxPriority+1 nếu không có priority
        int prio = priorityMap.value(name, maxPriority+1);

        // *viết lại công thức*:
        float score = 0.45f * cpu + 0.45f * mem + 0.1f * prio;
        if (score > maxScore) {
            maxScore = score;
            maxProc = proc;
        }
    }
    return maxProc;
}
