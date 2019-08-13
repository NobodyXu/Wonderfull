#define IN_PIN 2
#define OUT_PIN 13

void setup() {
  // put your setup code here, to run once:
  pinMode(IN_PIN, INPUT);
  pinMode(OUT_PIN, OUTPUT);
  Serial.begin(9600);
  interrupts();

  digitalWrite(OUT_PIN, LOW);
}


void button_status_changed() {
  if (digitalRead(IN_PIN) == LOW) {
    digitalWrite(OUT_PIN, HIGH);
    Serial.println(IN_PIN);
  } else {
    digitalWrite(OUT_PIN, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  attachInterrupt(digitalPinToInterrupt(IN_PIN), &button_status_changed, CHANGE);
  /*
  while (true) {
    digitalWrite(OUT_PIN, LOW);
      if (digitalRead(IN_PIN) == LOW) {
          digitalWrite(OUT_PIN, HIGH);
          Serial.println(IN_PIN);
      }
  }
  */
    /*

    while (true) {
      digitalWrite(7, HIGH);
      delay(500);
      digitalWrite(7, LOW);
      delay(500);
      digitalWrite(7, HIGH);
      delay(500);
      digitalWrite(7, LOW);
      delay(1000);
      digitalWrite(2, HIGH);
    }

    int button = digitalRead(2);
    Serial.println(button);

    delay(1000);
    */
}
