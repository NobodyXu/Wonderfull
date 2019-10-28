#include "Bluetooth.hpp"
#include "serial.hpp"

void setup() {
    delay(5000);
    serial.begin(9600);    
}

void loop() {
    auto bluetooth = core::Comm::Bluetooth{8, 7, 4};

    while (true) {
        bluetooth.info();
        serial.println("Enter anything to continue...");
        serial.getChar();
    }
}
