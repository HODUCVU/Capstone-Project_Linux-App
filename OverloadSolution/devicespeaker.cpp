#include "devicespeaker.h"
#include "../utils/processcommand.h"
#include <QString>

DeviceSpeaker::DeviceSpeaker()
    : ExecuteDeviceSpeakerCommand()
{}

void DeviceSpeaker::alertUserViaSound(int repeat, float freq, float length)
{
    QString command = getAlarmCommand(repeat, freq, length);
    ProcessCommand::execute(command);
}
