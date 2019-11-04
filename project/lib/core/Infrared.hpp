#ifndef  __Wonderfull_project_core_Sensor_Infrared_HPP__
# define __Wonderfull_project_core_Sensor_Infrared_HPP__

# include "digitalPin_t.hpp"

namespace core::Sensor {
class Infrared {
    digitalPin_t irReceiver;

public:
    Infrared(pin_t irReceiverPin);

    bool has_obstacles() const;
};
} /* namespace core::Sensor */

#endif
