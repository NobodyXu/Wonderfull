#define temp A0
#define red 9
#define green 10
#define blue 11

void setup() {
  Serial.begin(9600);
  pinMode(temp, INPUT);
  pinMode(red, OUTPUT); 
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

double analogRead_temp(int pin) {
  return (4.9 * analogRead(pin) - 500) / 10;
}


void loop() {
  double T = analogRead_temp(temp);
    
  analogWrite(red, 255);
  analogWrite(green, 255 - T / 15 * 85);
  analogWrite(blue, 0);

  Serial.println(T);
}
