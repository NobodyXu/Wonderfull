#include "Bluetooth.hpp"
#include "serial.hpp"

namespace core::Comm::impl {
void issue_command(Bluetooth &bt, const char *str, unsigned delayed_time = 1000) {
    serial.println(str);
    bt.print(str);

    bt.flush();
    delay(delayed_time);

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
    issue_command(*this, "AT+IMME?");
}

/*!
 * Since XC4382 by default is set as slave, nothing is required 
 * to be done here.
 */
void Bluetooth::as_slave() {
    ;
}

int Bluetooth::as_master(const char *slave_macAddress) {
    using impl::issue_command;

    issue_command(*this, "AT+IMME1");
    issue_command(*this, "AT+ROLE1");

    issue_command(*this, "AT+DISC?", 5000);

    print("AT+CON", slave_macAddress);
    ::serial.println("AT+CON", slave_macAddress);

    flush();
    delay(200);

    auto ret_msg = read(8);
    if (ret_msg.equals("AT+CONNE")) {
        ::serial.println("AT+CONNE");
        return -1;
    } else if (ret_msg.equals("AT+CONNF")) {
        ::serial.println("AT+CONNF");
        return 1;
    } else {
        ::serial.println("AT+CONNA");
        return 0;
    }
}
} /* namespace core::Comm */
