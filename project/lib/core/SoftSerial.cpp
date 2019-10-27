#include "SoftSerial.hpp"

namespace core::Comm {
SoftSerial::SoftSerial(pin_t RxD, pin_t TxD, unsigned bitrate):
    serial{RxD, TxD}
{
    serial.begin(bitrate);
}

bool SoftSerial::is_available() {
    return serial.available();
}

char SoftSerial::getChar() {
    while (!is_available())
        /* block */;
    return serial.read();
}

void SoftSerial::flush() {
    serial.flush();
}
} /* namespace core::Comm */
