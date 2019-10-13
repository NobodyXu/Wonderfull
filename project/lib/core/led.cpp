#include "led.hpp"

namespace core::effect {
led::led(pin_t pin_arg) noexcept:
    pin{pin_arg, digitalPin_t::Mode::output}
{}

led& led::setOn() noexcept {
    pin.write(digitalPin_t::Level::high);
    return *this;
}

led& led::setOff() noexcept {
    pin.write(digitalPin_t::Level::low);
    return *this;
}

led::~led() noexcept {
    setOff();
}
} /* namespace core::effect */
