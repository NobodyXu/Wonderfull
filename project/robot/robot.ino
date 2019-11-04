#include "serial.hpp"
#include "Bluetooth.hpp"
#include "Wheels.hpp"
#include "Infrared.hpp"

core::Comm::Bluetooth slave{10, 9, 8};
core::Motive::Wheels wheels{};

//core::Sensor::Infrared infraredFront{2, 3, 38000};
//core::Sensor::Infrared infraredRight{4, 5, 38000};
//core::Sensor::Infrared infraredLeft{6, 7, 38000};

void setup() {
    wheels.attach(13, 12);
    wheels.stayStill();
    delay(500);
}

class motor_coroutine {
    unsigned long long last_motor_ms = 0;
    
public:
    motor_coroutine() {}

    void run() {
        unsigned long long curr_time = millis();

        // Wait for 25 ms before making another move.
        if (curr_time - last_motor_ms < 25)
            return;

        if (slave.is_available()) {
            switch (slave.getChar_noblock()) {
                case 'F':
                    wheels.moveForward();
                    break;

                case 'B':
                    wheels.moveBackward();
                    break;

                case 'L':
                    wheels.turnLeft();
                    break;

                case 'R':
                    wheels.turnRight();
                    break;

                case 'S':
                    wheels.stayStill();
            }
        } else
            return;

        last_motor_ms = millis();
    }
};

motor_coroutine motor_co{};

void loop() {
    motor_co.run();

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
