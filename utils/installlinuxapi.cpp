#include "installlinuxapi.h"
#include "processcommand.h"
#include <QDebug>

InstallLinuxAPI::InstallLinuxAPI()
    : ExecuteInstallLinuxAPICommand()
{}

void InstallLinuxAPI::execute()
{
    QString command = getinstallCommand();
    QString output = ProcessCommand::execute(command);
    qDebug() << output;
}
