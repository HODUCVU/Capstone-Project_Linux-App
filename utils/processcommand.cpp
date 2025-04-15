#include "processcommand.h"
#include <QProcess>

ProcessCommand::ProcessCommand() {}

QString ProcessCommand::execute(QString command)
{
    QProcess process;
    process.start("/bin/bash", QStringList() << "-c" << command);
    process.waitForFinished();
    return process.readAllStandardOutput().trimmed();
}
