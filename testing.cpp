#include "testing.h"
#include "OverloadSolution/terminateprocesses.h"
#include "DeviceStats/SystemStats/systemstats.h"

Testing::Testing() {}

void Testing::TestingTerminateProcesses()
{
    QStringList PNames = {"brave", "chrome"};
    TerminateProcesses terminateCommand;
    terminateCommand.getPNamsFromMessage(PNames);
    terminateCommand.terminateProcessByPName();
}
