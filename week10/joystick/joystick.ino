#include "joystick.hpp"

void setup() {
    Serial.begin(9600);
}

using axis_t = typename joystick::axis;
using dir_t = typename axis_t::dir;
using pos_t = typename axis_t::pos;

joystick js{A4, A5, 2};

auto to_str(pos_t p) noexcept {
    if (p == pos_t::deadzone)
        return "deadzone";
    else if (p == pos_t::up)
        return "up";
    else if (p == pos_t::down)
        return "down";
    else
        return "unrecogonized direction";
}

void loop() {

    auto axis = js.read();

    Serial.print("x = ");
    Serial.print(to_str(axis.get(dir_t::x)));
    Serial.print(", y = ");
    Serial.print(to_str(axis.get(dir_t::y)));
    Serial.print(", z = ");
    Serial.println(to_str(axis.get(dir_t::z)));
}
