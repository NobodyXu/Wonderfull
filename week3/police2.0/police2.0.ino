#include <EEPROM.h>

#define buzzer 9
void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
}

unsigned int low = 300;
unsigned int high = 900;
unsigned int step = 1;

void loop() {
    // put your main code here, to run repeatedly:
    unsigned int freq = low;
    for (; freq < high; freq += step) {
      tone(buzzer, freq, 15);
    }
    for (; freq > low; freq -= step) {
      tone(buzzer, freq, 15);
    }
}
