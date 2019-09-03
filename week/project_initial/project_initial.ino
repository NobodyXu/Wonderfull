#define x_pin A0
#define y_pin A1
#define z_pin A2

#define first_pin 3
#define pin_cnt 8

#define foreach_segment() for (int i = 3; i != 11; ++i)

typedef struct segment {
  unsigned char segments;
} segment;

segment numbers[] = {
  {1 << 7 | 1 << 6 | 1 << 5 | 1 << 3 | 1 << 2 | 1 << 1}, // 0
  {1 << 5 | 1 << 2},                                     // 1
  {1 << 7 | 1 << 5 | 1 << 4 | 1 << 3 | 1 << 1},          // 2
  {1 << 7 | 1 << 5 | 1 << 4 | 1 << 2 | 1 << 1},          // 3
  {1 << 6 | 1 << 5 | 1 << 4 | 1 << 2},                   // 4
  {1 << 7 | 1 << 6 | 1 << 4 | 1 << 2 | 1 << 1},          // 5
  {1 << 7 | 1 << 6 | 1 << 4 | 1 << 3 | 1 << 2 | 1 << 1}, // 6
  {1 << 7 | 1 << 5 | 1 << 2},                            // 7
  {1 << 7 | 1 << 6 | 1 << 5 | 1 << 4 | 1 << 3 | 1 << 2 | 1 << 1}, // 8
  {1 << 7 | 1 << 6 | 1 << 5 | 1 << 4 | 1 << 2 | 1 << 1}, // 9
};

void print_segment(segment *s) {
  unsigned char mask = 1 << 7;

  //Serial.println(int(s->segments));
  foreach_segment() {
    //Serial.println((s->segments & mask));
    //Serial.println(int(mask));
    digitalWrite(i, (s->segments & mask) ? HIGH : LOW);
    mask >>= 1;
  }
}

void print_number(int num) {
  print_segment(&numbers[num]);
}

double read_G(int pin, double calibration) {
  const double to_volt = 0.0049;

  int unit = analogRead(pin);
  double Volt = unit * to_volt;
  return (Volt + calibration - 1.65) / 0.8;
}

void setup() {
  Serial.begin(9600);

  foreach_segment() {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void loop() {
  double z_G = read_G(z_pin, 0.35);

  for (int i = 0; i != 10; ++i) {
    if (z_G >= (0 + i * 0.1) && z_G < (0.099 + i * 0.1)) {
      print_number(9 - i);
      break;
    }
  }
  
  //Serial.println("x_G is: " + String(x_G) + " y_G is: " + String(y_G) + " z_G is: " + String(z_G));

  // z = 416-420 ... z_V = 2.04-2.06V // Flat          2.45V   0.4V
  // z = 263-265 ... z_V = 1.28-1.30V // On long edge  1.65V   0.35V
  // z = 254-257 ... z_V = 1.24-1.27V // On short edge 
  // z = 100-105 ... z_V = 0.45-0.51V // Upside-down   0.85V   0.35V

  // 
  
  // z = 683-691 ... z_V = 3.35-3.39 // Upside-down
  // 0.0049 V per unit

}
