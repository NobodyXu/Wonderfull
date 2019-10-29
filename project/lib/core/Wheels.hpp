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
    // 1536 is the value which the left stops
    static const int left_central_v = 1537;
    // 1530 is the value which the left stops
    static const int right_central_v = 1530;

    Wheels() noexcept; 

    void attach(pin_t left_pin, pin_t right_pin);

    void stayStill();
    void moveForward();
    void moveBackward();
    void turnLeft();
    void turnRight();

    ~Wheels() noexcept;
};
} /* namespace core::Motive */

#endif
