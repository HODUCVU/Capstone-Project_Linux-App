#ifndef DEVICESPEAKER_H
#define DEVICESPEAKER_H

#include "../utils/commands.h"

class DeviceSpeaker : ExecuteDeviceSpeakerCommand
{
public:
    DeviceSpeaker();
    void alertUserViaSound(int repeat = 3, float freq = 750, float length = 200);
};

#endif // DEVICESPEAKER_H
