#include <EEPROM.h>

#define LDR_PIN A0
#define BUZZER_PIN 13
void setup() {
    // put your setup code here, to run once:
    pinMode(LDR_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int in = analogRead(LDR_PIN);
    tone(BUZZER_PIN, in);
    Serial.println(in);
}
