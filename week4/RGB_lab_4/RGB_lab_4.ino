#define button 3
#define red 9
#define green 10
#define blue 11
//
//void button_released_and_pressed();

void setup() {
  Serial.begin(9600);
  
  pinMode(button, INPUT);
  pinMode(red, OUTPUT); 
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  interrupts();
  attachInterrupt(button, button_released_and_pressed, FALLING);
}

const unsigned long long length = 2 * 60 * 1000;
unsigned long long int curr;

void button_released_and_pressed() {
  curr += 1 * 60 * 1000;
}

void loop() {
  analogWrite(red, 255);
  analogWrite(green, 0);
  analogWrite(blue, 0);

  curr = 0;

  do {
    Serial.println(curr);
    analogWrite(green, 255 - (255 / length) * curr);
  } while (curr <= length);
}
