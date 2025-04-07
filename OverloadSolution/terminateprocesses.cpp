#include "terminateprocesses.h"
#include "../utils/processcommand.h"
#include <QString>

TerminateProcesses::TerminateProcesses()
    : ExecuteTerminateProcessesCommand()
{}

void TerminateProcesses::terminateProcessByPName(QString PName)
{
    QString command = getTerminateProcessCommand(PName);
    ProcessCommand::execute(command);
}
