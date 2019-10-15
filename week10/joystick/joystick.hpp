#ifndef  __Wonderfull_week9_joystick_joystick_HPP__
# define __Wonderfull_week9_joystick_joystick_HPP__

# include "bitfield.hpp"

class joystick {
    int x_pin, y_pin, z_pin;

public:
    joystick(int x_pin_arg, int y_pin_arg, int z_pin_arg) noexcept;

    class axis {
        unsigned char value = 0;

    public:
        enum class pos: unsigned char {
            deadzone = 0,
            up       = 1,
            down     = 2
        };
        enum class dir: unsigned char {
            x = 0,
            y = 2,
            z = 4
        };

        axis() = default;

        axis(const axis&) = default;
        axis& operator = (const axis&) = default;

        void set(dir, pos) noexcept;
        auto get(dir) const noexcept -> pos;
    };

    auto read() noexcept -> axis;
};

#endif
