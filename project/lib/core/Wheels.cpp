#include "Wheels.hpp"

namespace core::Motive {
Wheels::Wheels() noexcept {}

void Wheels::attach(pin_t left_pin, pin_t right_pin) {
    // Since by standard, servo should only accept pulse in range [1000, 2000], 
    // set it here so that Servo.write will obey.
    left.attach(left_pin, 1000, 2000);
    //left.attach(left_pin);
    right.attach(right_pin, 1000, 2000);
    //right.attach(right_pin);
}

void Wheels::stayStill() {
    // 1536 is the value which the left stops
    left.writeMicroseconds(left_central_v);
    // 1530 is the value which the left stops
    right.writeMicroseconds(right_central_v);
}

void Wheels::moveForward() {
    left.writeMicroseconds(left_central_v + 200);         // Left wheel turns counterclockwise
    right.writeMicroseconds(right_central_v - 200);        // Right wheel turns clockwise
}

void Wheels::moveBackward() {
    left.writeMicroseconds(left_central_v - 200);         // Left wheel turns clockwise
    right.writeMicroseconds(right_central_v + 200);        // Right wheel  turns counterclockwise
}

void Wheels::turnLeft() {
    left.writeMicroseconds(left_central_v - 200);         // Left wheel turns clockwise
    right.writeMicroseconds(right_central_v - 200);        // Right wheel turns clockwise
}

void Wheels::turnRight() {
    left.writeMicroseconds(left_central_v + 200);         // Left wheel turns counterclockwise
    right.writeMicroseconds(right_central_v + 200);        // Right wheel turns counterclockwise
}

Wheels::~Wheels() noexcept {
    left.detach();
    right.detach();
}
} /* namespace core::Motive */
