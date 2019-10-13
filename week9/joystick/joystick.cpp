// C++17
#include "joystick.hpp"
#include <Arduino.h>

using type = unsigned char;

void joystick::axis::set(dir d, pos p) noexcept {
    value |= type{p} << type{d};
}

constexpr auto get_mask(dir d) noexcept -> unsigned char {
    return (type{1} << type{d}) - 1;
}

auto joystick::axis::get(dir d) const noexcept -> pos {
    return pos{(value >> type{d}) & get_mask(d)};
}

joystick::joystick(int x_pin_arg, int y_pin_arg, int z_pin_arg) noexcept:
    x_pin{x_pin_arg}, y_pin{y_pin_arg}, z_pin{z_pin_arg}
{
    pinMode(x_pin, INPUT);
    pinMode(y_pin, INPUT);
    pinMode(z_pin, INPUT);
}

auto to_pos(int read) {
    if (read > 768)
        return axis::pos::up;
    else if (read < 256)
        return axis::pos::down;
}

auto joystick::read() noexcept -> axis {
    axis ret;

    auto x_read = analogRead(x_pin);
    auto y_read = analogRead(y_pin);
    auto z_read = digitalRead(z_pin);

    ret.set(axis::dir::x, to_pos(x_read));
    ret.set(axis::dir::y, to_pos(y_read));

    ret.set(axis::dir::z, axis::pos{!z_read});
}
