#include "Bluetooth.hpp"
#include "serial.hpp"

namespace core::Comm::impl {
void issue_command(Bluetooth &bt, const char *str) {
    serial.println(str);
    bt.print(str);

    bt.flush();
    delay(1000);

    bt.forward(serial);
    
    serial.println();
    serial.flush();
}
} /* namespace impl */

namespace core::Comm {
Bluetooth::Bluetooth(pin_t RxD, pin_t TxD, pin_t resetPin):
    base_t{RxD, TxD}, reset{resetPin, digitalPin_t::Mode::output}
{
    reset.write(digitalPin_t::Level::high);
    base_t::begin(9600);
}

void Bluetooth::info() {
    using impl::issue_command;

    issue_command(*this, "AT");
    issue_command(*this, "AT+BAUD?");
    issue_command(*this, "AT+PASS?");
    issue_command(*this, "AT+ROLE?");
    issue_command(*this, "AT+ADDR?");
}

/*!
 * Since XC4382 by default is set as slave, nothing is required 
 * to be done here.
 */
void Bluetooth::as_slave() {
    ;
}
} /* namespace core::Comm */
