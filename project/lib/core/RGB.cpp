#include "RGB.hpp"
#include <Arduino.h>

namespace core::Effect {
RGB::RGB(pin_t red_pin, pin_t green_pin, pin_t blue_pin):
    Red{red_pin,   digitalPin_t::Mode::output},
    Gre{green_pin, digitalPin_t::Mode::output},
    Blu{blue_pin,  digitalPin_t::Mode::output}
{}

void RGB::setRed() {
    Red.write(digitalPin_t::Level::high);
}

void RGB::setGre() {
    Gre.write(digitalPin_t::Level::high);
}

void RGB::setBlu() {
    Blu.write(digitalPin_t::Level::high);
}

void RGB::unsetRed() {
    Red.write(digitalPin_t::Level::low);
}

void RGB::unsetGre() {
    Gre.write(digitalPin_t::Level::low);
}

void RGB::unsetBlu() {
    Blu.write(digitalPin_t::Level::low);
}
} /* namespace core::Effect */
