#include "Serial.hpp"

void setup() {
    Serial.begin(9600);

    delay(10000);
    println(Serial, "This is a test...", "\n", "test/lib/core/SoftSerial/SoftSerial.ino");
}

void loop() {
    println(Serial, "Enter anything to test the echo: ");
    println(Serial, getChar(Serial));
}
