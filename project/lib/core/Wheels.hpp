#ifndef  __Wonderfull_project_core_Motive_Wheels_HPP__
# define __Wonderfull_project_core_Motive_Wheels_HPP__

# include "types.hpp"

# include <Arduino.h>
# include <Servo.h>

namespace core::Motive {
class Wheels {
    Servo left;
    Servo right;

public:
    Wheels(pin_t left_pin, pin_t right_pin) noexcept; 

    void moveForward(int time);
    void moveBackward(int time);
    void turnLeft(int time);
    void turnRight(int time);

    ~Wheels() noexcept;
};
} /* namespace core::Motive */

#endif