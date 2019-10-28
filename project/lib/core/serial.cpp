#include "serial.hpp"

core::Comm::Serial<HardwareSerial&> serial = core::Comm::Serial<HardwareSerial&>(Serial);
