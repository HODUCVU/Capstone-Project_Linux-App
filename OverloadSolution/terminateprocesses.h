#ifndef TERMINATEPROCESSES_H
#define TERMINATEPROCESSES_H

#include "../utils/commands.h"
#include <QStringList>

class TerminateProcesses : public ExecuteTerminateProcessesCommand
{
public:
    TerminateProcesses();
    void terminateProcessByPName(QString PName);
};

#endif // TERMINATEPROCESSES_H
