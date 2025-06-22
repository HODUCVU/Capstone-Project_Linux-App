#!/usr/bin/bash

echo "###########################################################################################################"
echo "******************************** Beginning setup environment for Linux App ********************************"
echo "###########################################################################################################"

echo "🔁 Updating apt packages..."
sudo apt update

packages=("procps" "util-linux" "sysstat" "lm-sensors" "psmisc" "stress" "beep" "sox")
echo "🔁 Checking installed packages..."

for package in "${packages[@]}"; do 
  if (! dpkg -s "$package" &> /dev/null); then
    echo "🔁 Installing package ($package)..."
    sudo apt install "$package"
    echo "✅ Installed ($package)"
  else 
    echo "✅ Require package ($package) is installed"
  fi
done

if [[ -f IVI-System-App ]]; then
  chmod a+x IVI-System-App
elif [[ -f IVI-system-Linux-App ]]; then
  chmod a+x IVI-system-Linux-App
else
  echo "❗ You need to download IVI-system-Linux-App and put it in the same folder as $(basename \"$0\")"
  exit 1
fi
echo "###########################################################################################################"
echo "***** Successfully established the environment, hope you have a pleasant experience with our products *****"
echo "###########################################################################################################"

