#include "bluetooth.hpp"

void setup() {
    // Wait for serial monitor to be opened
    delay(20000);
    Serial.begin(9600);
    Serial.println("Serial initialized...");
}

void loop() {
    Serial.println("Start to initialize bluetooth...");
    auto slave = core::Control::Bluetooth::slave(6, 7, A1, 1);
    Serial.println("Bluetooth is ready...");

    while (1) {
        if(slave.is_available())
            Serial.print(slave.read());

        if(Serial.available()) {
            auto recvChar  = Serial.read();
            Serial.print(recvChar);
            slave.print(recvChar);
        }
    }
}
