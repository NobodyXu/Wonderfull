#!/bin/bash

warn() {
    echo $@
    read
}

warn "Before continue, please make sure that neovim is intalled! Press any key to continue, or ctrl-c to terminate..."

mkdir -p ~/Development/

# Clone project repo
git clone https://github.com/NobodyXu/Wonderfull ~/Development/Wondefull

# Install Arduino-Makefile which is necessary for multi file arduino development.
git clone https://github.com/sudar/Arduino-Makefile ~/Development/Arduino-Makefile

cat >> ~/.bashrc << EOF
# This is for arduino development environment
export ARDUINO_DIR=${HOME}/.local/arduino-1.8.10
export ARDMK_DIR=${HOME}/Development/Arduino-Makefile
export ARDMKFILE=${ARDMK_DIR}/Arduino.mk
export AVR_TOOLS_DIR=${HOME}/.local/arduino-1.8.10/hardware/tools/avr

export PATH=${AVR_TOOLS_DIR}/bin:$PATH
EOF

# Install nvim-as-ide
git clone https://github.com/NobodyXu/nvim-as-ide ~/Development/nvim-as-ide
source ~/Development/nvim-as-ide/install.sh

warn -e "A test over your terminal will be carried out to make sure that you can run neovim without any error\n"
        "After the test, please fix all error that is not marked as non-optional\n"
        "Press any key to continue..."
source ~/Development/nvim-as-ide/check_nvim_env.sh

warn -e "Please restart your bash by 'exec bash' or restart your terminal after the script exits.\n"
        "Press any key to continue..."
