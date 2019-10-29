#include "serial.hpp"
#include "Bluetooth.hpp"
#include "Wheels.hpp"
#include "Infrared.hpp"

core::Comm::Bluetooth slave{10, 9, 8};
core::Motive::Wheels wheels{};

core::Sensor::Infrared infraredFront{2, 3, 38000};
core::Sensor::Infrared infraredRight{4, 5, 38000};
core::Sensor::Infrared infraredLeft{6, 7, 38000};

void setup() {
    wheels.attach(13, 12);
    wheels.stayStill();
    delay(500);
}

void loop() {
    if (slave.is_available()) {
        auto ch = slave.getChar_noblock();
        if (ch == 'F') {
            wheels.moveForward();
        } else if (ch == 'B') {
            wheels.moveBackward();
        } else if (ch == 'L') {
            wheels.turnLeft();
        } else if (ch == 'R') {
            wheels.turnRight();
        } else if (ch == 'S') {
            wheels.stayStill();
        }

        delay(25);
    }

    /*
    if (infraredFront.has_obstacles()) {
        slave.print('F');
    }
    if (infraredRight.has_obstacles()) {
        slave.print('R');
    }
    if (infraredLeft.has_obstacles()) {
        slave.print('L');
    }

    slave.flush();
    */
}
