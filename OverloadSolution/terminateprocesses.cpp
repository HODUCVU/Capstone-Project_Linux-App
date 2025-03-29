#include "terminateprocesses.h"
#include "../utils/processcommand.h"
#include <QDebug>

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
    QString command;
    for(const auto PName : PNames) {
        command = getTerminateProcessCommand(PName);
        ProcessCommand::execute(command);
    }
}
