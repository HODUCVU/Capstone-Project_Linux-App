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

void TerminateProcesses::getPNamsFromMessage(QStringList PNames)
{
    this->PNames = PNames;
}

void TerminateProcesses::terminateProcessByPName()
{
    for(QString &PName : PNames) {
        QString command = getTerminateProcessCommand(PName);
        ProcessCommand::execute(command);
    }
}
