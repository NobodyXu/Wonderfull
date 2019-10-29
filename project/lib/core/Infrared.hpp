#ifndef  __Wonderfull_project_core_Sensor_Infrared_HPP__
# define __Wonderfull_project_core_Sensor_Infrared_HPP__

# include "digitalPin_t.hpp"

namespace core::Sensor {
class Infrared {
    digitalPin_t irLed;
    digitalPin_t irReceiver;
    unsigned long frequency;

public:
    Infrared(pin_t irLedPin, pin_t irReceiverPin, unsigned long freq) noexcept;

    bool has_obstacles() const noexcept;
};
} /* namespace core::Sensor */

#endif
