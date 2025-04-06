#include "terminateprocesses.h"
#include "../utils/processcommand.h"
#include <QString>

TerminateProcesses::TerminateProcesses()
    : ExecuteTerminateProcessesCommand()
{}

TerminateProcesses::~TerminateProcesses()
{
    this->PNames.clear();
}

void TerminateProcesses::terminateProcessByPName(QString PName)
{
    QString command = getTerminateProcessCommand(PName);
    ProcessCommand::execute(command);
}

// void TerminateProcesses::setPNamsFromMessage(QStringList PNames)
// {
//     this->PNames = PNames;
// }

// void TerminateProcesses::terminateProcessesByPName()
// {
//     for(QString &PName : PNames) {
//         terminateProcessByPName(PName);
//     }
// }
