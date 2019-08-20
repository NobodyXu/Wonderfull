#define IN_PIN 2

int map_bit_to_pin(int bit) {
  return bit + 10;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(IN_PIN, INPUT);

  int bit = 0;
  for ( ; bit != 4; ++bit) {
      int pin = map_bit_to_pin(bit);
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
  }

  attachInterrupt(digitalPinToInterrupt(IN_PIN), &button_status_changed, RISING);
  interrupts();
}

int num = 0;

void button_status_changed() {
  num = (num + 1) % 16;
  int bit = 0;
  for ( ; bit != 4; ++bit) {
    digitalWrite(map_bit_to_pin(bit), (num >> bit) & 1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
