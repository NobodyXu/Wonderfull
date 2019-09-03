[code]
#include<Servo.h>

#define x_pin A0
#define y_pin A1
#define z_pin A2
#define servo_pin 9

bool print_and_ret(bool val) {
  Serial.println(val);
  return val;
}

int i = 0;
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(servo_pin);
}

double read_G(int pin, double calibration) {
  const double to_volt = 0.0049;

  int unit = analogRead(pin);
  double Volt = unit * to_volt;
  return (Volt + calibration - 1.65) / 0.8;
}

bool changed_alot(double prev_G, double curr_G) {
  double diff = abs(curr_G - prev_G);
  return diff >= abs(prev_G * 0.1) && diff > 0.1;
}

int degree = 0;
double prev_x_G = 0;
double prev_y_G = 0;
double prev_z_G = 0;

void loop() {
  double x_G = read_G(x_pin, 0.08);
  double y_G = read_G(y_pin, -0.08);
  double z_G = read_G(z_pin, 0.35);

  Serial.println("prev_x_G is: " + String(prev_x_G) + " y_G is: " + String(prev_y_G) + " z_G is: " + String(prev_z_G));
  Serial.println("x_G is: " + String(x_G) + " y_G is: " + String(y_G) + " z_G is: " + String(z_G));

  if (print_and_ret(changed_alot(x_G, prev_x_G)) ||
      print_and_ret(changed_alot(y_G, prev_y_G)) ||
      print_and_ret(changed_alot(z_G, prev_z_G)))
  {
    degree = 0;
    Serial.println("Resetting...");
  }

  prev_x_G = x_G;
  prev_y_G = y_G;
  prev_z_G = z_G;

  servo.write(degree);

  degree += 2;
  
  delay(100);

  // z = 416-420 ... z_V = 2.04-2.06V // Flat          2.45V   0.4V
  // z = 263-265 ... z_V = 1.28-1.30V // On long edge  1.65V   0.35V
  // z = 254-257 ... z_V = 1.24-1.27V // On short edge 
  // z = 100-105 ... z_V = 0.45-0.51V // Upside-down   0.85V   0.35V

  // 
  
  // z = 683-691 ... z_V = 3.35-3.39 // Upside-down
  // 0.0049 V per unit

}
[/code]
