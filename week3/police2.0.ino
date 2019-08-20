#include <EEPROM.h>

#define buzzer 9
void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
}

void loop() {
    // put your main code here, to run repeatedly:
    unsigned int freq = 700;
    for (; freq < 960; ++freq) {
      tone(buzzer, freq, 15);
    }
    for (; freq > 700; --freq) {
      tone(buzzer, freq, 15);
    }
}
