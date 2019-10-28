#include "serial.hpp"

void setup() {
    delay(5000);
    serial.begin(9600);
    serial.println("This is a test...", "\n", "test/lib/core/SoftSerial/SoftSerial.ino");
}

void loop() {
    for (int i = 0; i != 10; ++i) {
        serial.println("Enter anything to test the echo: ");
        serial.println(serial.getChar());
    }

    for (int i = 0; i != 10; ++i) {
        serial.println("Enter string here to test read(10): ");
        serial.println(serial.read(10));
    }
}
