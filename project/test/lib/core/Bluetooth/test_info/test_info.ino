#include "Bluetooth.hpp"
#include "serial.hpp"

void setup() {
    delay(5000);
    serial.begin(9600);    
}

void loop() {
    auto bluetooth = core::Comm::Bluetooth{8, 7, 4};
    serial.println("Testing bluetooth module...");
    bluetooth.info();
    serial.println("Test done, start waiting for connection...");


    while (true) {
        if (bluetooth.is_available()) {
            bluetooth.print(bluetooth.getChar_noblock());
            bluetooth.flush();
        }
    }
}
