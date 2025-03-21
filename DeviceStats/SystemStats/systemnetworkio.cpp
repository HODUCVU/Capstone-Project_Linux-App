#include "systemnetworkio.h"
#include "../../utils/processcommand.h";

SystemNetworkIO::SystemNetworkIO()
    : ExecuteSystemNetworkIOCommand()
{
    getNetworkInterfaceTypeFromDevice();
    totalReceivedMB = 0.0;
    totalSentMB = 0.0;
}

float SystemNetworkIO::getReceivingSpeed()
{
    return receiving;
}

float SystemNetworkIO::getSendingSpeed()
{
    return sending;
}

float SystemNetworkIO::getTotalReceivedMB()
{
    return totalReceivedMB;
}

float SystemNetworkIO::getTotalSentMB()
{
    return totalSentMB;
}

void SystemNetworkIO::getNetworkInterfaceTypeFromDevice()
{
    QString command = getnetworkInterfaceTypeCommand();
    QString output = ProcessCommand::execute(command);
    this->interface = output.isEmpty() ? "enp0s31f6" : output;
}

void SystemNetworkIO::getNetworkReceiveFromDevice()
{
    QString command = getTotalReceivedCommand(this->interface);
    QString output = ProcessCommand::execute(command);
    float currentReceivedMB = output.toFloat()/(1024.0*1024);
    calculateReceivingSpeed(currentReceivedMB);
    this->totalReceivedMB = currentReceivedMB;
}
void SystemNetworkIO::calculateReceivingSpeed(float currentReceivedMB)
{
    this->receiving = (currentReceivedMB - this->totalReceivedMB)*1024.0; // Kb/s
}

void SystemNetworkIO::getNetworkSendFromDevice()
{
    QString command = getTotalSentCommand(this->interface);
    QString output = ProcessCommand::execute(command);
    float currentSentMB = output.toFloat()/(1024.0*1024);
    calculateSendingSpeed(currentSentMB);
    this->totalSentMB = currentSentMB;
}
void SystemNetworkIO::calculateSendingSpeed(float currentSentMB)
{
    this->sending = (currentSentMB - this->totalSentMB)*1024.0; // Kb
}
