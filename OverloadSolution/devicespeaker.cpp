#include "devicespeaker.h"
#include "../utils/processcommand.h"
#include <QString>

DeviceSpeaker::DeviceSpeaker()
    : ExecuteDeviceSpeakerCommand(), isAlert(false)
{}

void DeviceSpeaker::alertUserViaSound(int repeat, float freq, float length)
{
    QString command = getAlarmCommand(repeat, free, length);
    ProcessCommand::execute(command);
}
