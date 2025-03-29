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
    void getPNamsFromMessage(QStringList PNames);
    void terminateProcessByPName();
};

#endif // TERMINATEPROCESSES_H
