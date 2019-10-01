#include "led.hpp"

namespace core::effect {
led::led(pin_t pin_arg) noexcept:
    pin{pin_arg}
{
    pinMode(pin, OUTPUT);
}

led& led::setOn() noexcept {
    digitalWrite(pin, HIGH);
    return *this;
}

led& led::setOff() noexcept {
    digitalWrite(pin, LOW);
    return *this;
}

led::~led() noexcept {
    setOff();
}
} /* namespace core::effect */
