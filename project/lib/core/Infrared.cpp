#include "Infrared.hpp"

namespace core::Sensor {
Infrared::Infrared(pin_t irLedPin, pin_t irReceiverPin, int freq) noexcept:
    irLed{irLedPin, digitalPin_t::Mode::output}, 
    irReceiver{irReceiverPin, digitalPin_t::Mode::input},
    frequency{freq}
{}

bool Infrared::has_obstacles() const noexcept {
  irLed.tone(frequency, 8);               // IRLED 38 kHz for at least 1 ms
  delay(1);                               // Wait 1 ms
  auto ir = irReceiver.read();            // IR receiver -> ir variable
  delay(1);                               // Down time before recheck
  return ir == digitalPin_t::Level::high; // Return 1 no detect, 0 detect
}
} /* namespace core::Sensor */
