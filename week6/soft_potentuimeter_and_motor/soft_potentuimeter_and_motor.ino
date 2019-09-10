#define POTENT_PIN A0
#define MOTOR_PIN 9

void setup() {
  // put your setup code here, to run once:
  pinMode(POTENT_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //analogWrite(MOTOR_PIN, 0);
  /*
    analogWrite(MOTOR_PIN, 256);
    delay(10000);
  for (int i = 36; i != 256; ++i) {
    analogWrite(MOTOR_PIN, i);
    delay(1000);
  }*/
  
  int raw_input = analogRead(POTENT_PIN);
  Serial.print("Raw: ");
  Serial.println(raw_input);
  
  double volt = raw_input * 0.0049;
  Serial.print("Voltage: ");
  Serial.println(volt);

  double resistance = volt / (5.02 - volt) * 10000;
  Serial.print("Resistance: ");
  Serial.println(resistance);


  unsigned char out = 255 - raw_input / 1023 * 255;
  Serial.print("Output: ");
  Serial.println(out);
  Serial.println();
  analogWrite(MOTOR_PIN, out);
}
