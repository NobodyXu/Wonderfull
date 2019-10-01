#ifndef  __Wonderfull_project_core_effect_led_HPP__
# define __Wonderfull_project_core_effect_led_HPP__

# include "types.hpp"

namespace core::effect {
struct led {
    pin_t pin;

public:
    led(pin_t) noexcept;

    led& setOn() noexcept;
    led& setOff() noexcept;

    ~led() noexcept;
};
} /* namespace core::effect */

#endif
