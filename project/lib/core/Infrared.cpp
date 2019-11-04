#include "Infrared.hpp"

namespace core::Sensor {
Infrared::Infrared(pin_t irReceiverPin):
    irReceiver{irReceiverPin, digitalPin_t::Mode::input}
{}

bool Infrared::has_obstacles() const {
    return irReceiver.read() == digitalPin_t::Level::low; // Return 1 no detect, 0 detect
}
} /* namespace core::Sensor */
