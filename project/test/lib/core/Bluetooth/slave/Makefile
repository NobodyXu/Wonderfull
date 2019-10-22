BOARD_TAG := uno
#MONITOR_PORT := /dev/ttyACM1

# The following line is learnt from:
#     https://stackoverflow.com/a/25817631
print-% : ; @echo $* = $($*)

USER_LIB_PATH := $(realpath ../../../../../lib)
ARDUINO_LIBS := core meta SoftwareSerial Servo
CXXFLAGS_STD := -std=c++17 -flto

include $(ARDMKFILE)
