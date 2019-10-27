#include "SoftSerial.hpp"

using core::Comm::SoftSerial;

SoftSerial usb(0, 1, 9600);

void setup() {
    delay(10000);
    usb.println("This is a test...", "\n", "test/lib/core/SoftSerial/SoftSerial.ino");
}

void loop() {
    usb.println("Enter anything to test the echo: ");
    usb.println(usb.getChar());
}
