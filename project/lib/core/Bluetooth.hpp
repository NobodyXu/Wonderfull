#ifndef  __Wonderfull_project_core_Comm_Bluetooth_HPP__
# define __Wonderfull_project_core_Comm_Bluetooth_HPP__

# include "digitalPin_t.hpp"
# include "Serial.hpp"
# include <SoftwareSerial.h>

namespace core::Comm {
/*!
 * Bluetooth for XC4382.
 */
class Bluetooth: private Serial<SoftwareSerial> {
    digitalPin_t reset;

    using base_t = Serial<SoftwareSerial>;

public:
    /*!
     * @ RxD This pin should be connected to TxD on the bluetooth module.
     * @ TxD This pin should be connected to RxD on the bluetooth module.
     * @ resetPin This pin should be connected to BRK on the bluetooth module,
     *            which is used to reset bluetooth connection.
     */
    Bluetooth(pin_t RxD, pin_t TxD, pin_t resetPin);

    Bluetooth() = delete;

    Bluetooth(const Bluetooth&) = delete;
    Bluetooth(Bluetooth&&) = delete;

    Bluetooth& operator = (const Bluetooth&) = delete;
    Bluetooth& operator = (Bluetooth&&) = delete;

    /*!
     * Only expose interface of base class if necessary
     */
    using base_t::is_available;
    using base_t::wait_for_available;

    using base_t::getChar_noblock;
    using base_t::getChar;
    using base_t::read;

    using base_t::print;
    using base_t::println;
    using base_t::forward;

    using base_t::flush;

    /*!
     * print information about the bluetooth to usb.
     */
    void info();

    /*!
     * as_slave() will set the device as slave and make
     * it ready to be query
     */
    void as_slave();
    /*!
     * Returns 0  for success,
     *         -1 for error,
     *         1  for failure.
     */
    int as_master(const char *slave_macAddress);
};
} /* namespace core::Comm */

#endif
