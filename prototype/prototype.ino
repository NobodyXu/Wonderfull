#define LDR_PIN A0
#define BUZZER_PIN 13
void setup() {
    // put your setup code here, to run once:
    pinMode(LDR_PIN, INPUT);
    //pinMode(BUZZER_PIN, OUTPUT);
   // Serial.begin(9600);
}

void loop() {
    int in = analogRead(LDR_PIN);
    if (900 < in < 1000) {
    for (int i = 0; i < 9; i++) {
      tone(BUZZER_PIN, 1000);    
      }
    }
    else if (800 < in < 900) {
    for (int i = 0; i < 8; i++) {
      tone(BUZZER_PIN, 1000);    
      }
    }
    else if (100 < in < 200) {
    for (int i = 0; i < 7; i++) {
      tone(BUZZER_PIN, 1000);    
    }
    }
   // Serial.println(in);
}
