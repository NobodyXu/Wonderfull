#include "Bluetooth.hpp"
#include "serial.hpp"

auto bluetooth = core::Comm::Bluetooth{8, 7, 4};

void setup() {
    delay(5000);
    serial.begin(9600);    

    serial.println("Testing bluetooth module...");
    bluetooth.info();
    serial.println("Test done, start waiting for connection...");
}

void loop() {
    if (bluetooth.is_available()) {
        bluetooth.print(bluetooth.getChar_noblock());
        bluetooth.flush();
    }
}
