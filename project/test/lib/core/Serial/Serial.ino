#include "digitalPin_t.hpp"
#include "Serial.hpp"

auto serial = core::Comm::Serial<HardwareSerial&>(Serial);

void setup() {
    delay(5000);
    serial.begin(9600);
    serial.println("This is a test...", "\n", "test/lib/core/SoftSerial/SoftSerial.ino");
}

void loop() {
    serial.println("Enter anything to test the echo: ");
    serial.println(serial.getChar());
}
