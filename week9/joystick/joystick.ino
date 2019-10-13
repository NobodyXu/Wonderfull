#include "joystick.hpp"

void setup() {
    Serial.begin(9600);
}

joystick js{A4, A5, 2};

void loop() {
    // The code here is outdated now.
    // It won't work anymore.
    // It was just for demo purpose.
    auto axis = js.read();

    Serial.print("x = ");
    Serial.print(axis.x);
    Serial.print(", y = ");
    Serial.print(axis.y);
    Serial.print(", z = ");
    Serial.println(axis.z ? "True" : "False");
}
