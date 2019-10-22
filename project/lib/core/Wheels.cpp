#include "Wheels.hpp"

namespace core::Motive {
Wheels::Wheels(pin_t left_pin, pin_t right_pin) noexcept {
    // Since by standard, servo should only accept pulse in range [1000, 2000], 
    // set it here so that Servo.write will obey.
    left.attach(left_pin, 1000, 2000);
    right.attach(right_pin, 1000, 2000);
}

void Wheels::moveForward(int time) {
    left.writeMicroseconds(1700);         // Left wheel turns counterclockwise
    right.writeMicroseconds(1300);        // Right wheel turns clockwise
    delay(time);                               // Move for time ms
}

void Wheels::moveBackward(int time) {
    left.writeMicroseconds(1300);         // Left wheel turns clockwise
    right.writeMicroseconds(1700);        // Right wheel  turns counterclockwise
    delay(time);                               // Move for time ms
}

void Wheels::turnLeft(int time) {
    left.writeMicroseconds(1300);         // Left wheel turns clockwise
    right.writeMicroseconds(1300);        // Right wheel turns clockwise
    delay(time);                               // Move for time ms
}

void Wheels::turnRight(int time) {
    left.writeMicroseconds(1700);         // Left wheel turns counterclockwise
    right.writeMicroseconds(1700);        // Right wheel turns counterclockwise
    delay(time);                               // Move for time ms
}

Wheels::~Wheels() noexcept {
    left.detach();
    right.detach();
}
} /* namespace core::Motive */
