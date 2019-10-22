// C++17
#include "joystick.hpp"
#include <Arduino.h>

namespace core::Control {
using type = unsigned char;

// Impl of joystick::axis
void joystick::axis::set(dir d, pos p) noexcept {
    value |= static_cast<type>(p) << static_cast<type>(d);
}

// Calculate the mask for getting 2 bits out of 8 bits.
// 
// It will return 11B.
constexpr auto get_mask() noexcept -> unsigned char {
    return (type{1} << type{2}) - 1;
}

auto joystick::axis::get(dir d) const noexcept -> pos {
    return pos{static_cast<type>(value >> static_cast<type>(d)) & get_mask()};
}

// Impl of joystick
joystick::joystick(int x_pin_arg, int y_pin_arg, int z_pin_arg) noexcept:
    x_pin{x_pin_arg}, y_pin{y_pin_arg}, z_pin{z_pin_arg}
{
    pinMode(x_pin, INPUT);
    pinMode(y_pin, INPUT);
    pinMode(z_pin, INPUT);
}

auto to_pos(int read) {
    if (read > 768)
        return joystick::axis::pos::up;
    else if (read < 256)
        return joystick::axis::pos::down;
    else
        return joystick::axis::pos::deadzone;
}

auto joystick::read() noexcept -> axis {
    axis ret;

    auto x_read = analogRead(x_pin);
    auto y_read = analogRead(y_pin);
    auto z_read = digitalRead(z_pin);

    ret.set(axis::dir::x, to_pos(x_read));
    ret.set(axis::dir::y, to_pos(y_read));

    // Since z returns 0 on triggered, 1 on not.
    ret.set(axis::dir::z, axis::pos{!z_read});

    return ret;
}
} /* namespace core::Control */
