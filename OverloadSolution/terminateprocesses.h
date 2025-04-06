#ifndef TERMINATEPROCESSES_H
#define TERMINATEPROCESSES_H

#include "../utils/commands.h"
#include <QStringList>

class TerminateProcesses : public ExecuteTerminateProcessesCommand
{
private:
    QStringList PNames;
public:
    TerminateProcesses();
    ~TerminateProcesses();
    void terminateProcessByPName(QString PName);
    // void setPNamsFromMessage(QStringList PNames);
    // void terminateProcessesByPName();
};

#endif // TERMINATEPROCESSES_H
