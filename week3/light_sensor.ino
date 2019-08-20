#include <EEPROM.h>

#define LDR_PIN A0
void setup() {
    // put your setup code here, to run once:
    pinMode(LDR_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
   Serial.println(analogRead(LDR_PIN) * 0.049);
}
