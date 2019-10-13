BOARD_TAG := uno

# The following line is learnt from:
#     https://stackoverflow.com/a/25817631
print-% : ; @echo $* = $($*)

USER_LIB_PATH := $(realpath ./lib)
ARDUINO_LIBS := core
CXXFLAGS_STD := -std=c++17 -flto

include $(ARDMKFILE)
