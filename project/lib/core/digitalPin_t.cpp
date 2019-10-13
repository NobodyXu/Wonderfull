#include "digitalPin_t.hpp"

#include <Arduino.h>

namespace core {
digitalPin_t::digitalPin_t(pin_t pin_arg, Mode mode) noexcept:
    pin{pin_arg}
{
    pinMode(pin, static_cast<int>(mode));
}

auto digitalPin_t::read() const noexcept -> Level {
    return Level{static_cast<bool>(digitalRead(pin))};
}

void digitalPin_t::write(Level level) const noexcept {
    digitalWrite(pin, static_cast<bool>(level));
}

void digitalPin_t::tone(unsigned frequency) const noexcept {
    tone(pin, frequency);
}

void digitalPin_t::tone(unsigned frequency, unsigned long duration) const noexcept {
    ::tone(pin, frequency, duration);
}

void digitalPin_t::noTone() const noexcept {
    ::noTone(pin);
}

void digitalPin_t::pulseIn(Level l) const noexcept {
    ::pulseIn(pin, static_cast<bool>(l));
}

void digitalPin_t::pulseIn(Level l, unsigned timeout) const noexcept {
    ::pulseIn(pin, static_cast<bool>(l), timeout);
}

void digitalPin_t::pulseInLong(Level l) const noexcept {
    ::pulseInLong(pin, static_cast<bool>(l));
}

void digitalPin_t::pulseInLong(Level l, unsigned timeout) const noexcept {
    ::pulseInLong(pin, static_cast<bool>(l), timeout);
}

auto digitalPin_t::raw() const noexcept -> pin_t {
    return pin;
}

digitalPin_t::~digitalPin_t() noexcept {
    // Currently, this function does nothing.
    ;
}
} /* namespace core */
