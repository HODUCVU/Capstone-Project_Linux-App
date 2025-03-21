#ifndef SYSTEMNETWORKIO_H
#define SYSTEMNETWORKIO_H

#include "../../utils/commands.h"

class SystemNetworkIO : ExecuteSystemNetworkIOCommand
{
private:
    QString interface;
    float receiving;
    float sending;
    float totalReceivedMB;
    float totalSentMB;
public:
    SystemNetworkIO();
    // Getter
    float getReceivingSpeed();
    float getSendingSpeed();
    float getTotalReceivedMB();
    float getTotalSentMB();

    void getNetworkReceiveFromDevice();
    void getNetworkSendFromDevice();
private:
    void getNetworkInterfaceTypeFromDevice();
    void calculateReceivingSpeed(float currentReceivedMB);
    void calculateSendingSpeed(float currentSentMB);
};

#endif // SYSTEMNETWORKIO_H
