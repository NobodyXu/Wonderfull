#include "bluetooth.hpp"

void setup() {
    // Wait for serial monitor to be opened
    delay(20000);
    Serial.begin(9600);
    Serial.println("Serial initialized...");
}


void loop() {
    Serial.println("Start to initialize bluetooth...");
    auto master = core::Control::Bluetooth::master(6, 7, A1, 1);
    Serial.println("Bluetooth is ready...");

    while (1) {
        if(master.is_available())
            Serial.print(master.read());

        if(Serial.available()) {
            auto recvChar  = Serial.read();
            Serial.print(recvChar);
            master.print(recvChar);
        }
    }
}
