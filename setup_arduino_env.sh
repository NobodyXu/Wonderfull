#!/bin/bash

mkdir -p ~/Development/

# Install arduino ide as it is required by Arduino-Makefile
cd /tmp && wget https://downloads.arduino.cc/arduino-1.8.10-linux64.tar.xz
mkdir -p ~/.local/arduino-1.8.10
## Extract it
cd ~/.local/arduino-1.8.10 && tar xf /tmp/arduino-1.8.10-linux64.tar.xz

# Install Arduino-Makefile which is necessary for multi file arduino development.
git clone https://github.com/sudar/Arduino-Makefile ~/Development/Arduino-Makefile

# This is for arduino development environment
echo 'export ARDUINO_DIR=${HOME}/.local/arduino-1.8.10'                      >> ${HOME}/.bashrc
echo 'export ARDMK_DIR=${HOME}/Development/Arduino-Makefile'                 >> ${HOME}/.bashrc
echo 'export ARDMKFILE=${ARDMK_DIR}/Arduino.mk'                              >> ${HOME}/.bashrc
echo 'export AVR_TOOLS_DIR=${HOME}/.local/arduino-1.8.10/hardware/tools/avr' >> ${HOME}/.bashrc
echo 'export PATH=${AVR_TOOLS_DIR}/bin:$PATH' >> ${HOME}/.bashrc
