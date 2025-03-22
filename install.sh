#!/bin/bash

echo "Updating package lists..."
sudo apt update

echo "Installing required packages..."
sudo apt install -y qtbase5-dev mpstat sysstat lm-sensors ifstat

echo "install ps package"
sudo apt install procps
echo "Installation complete!"
