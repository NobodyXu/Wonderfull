#define temp A0

void setup() {
  Serial.begin(9600);
  pinMode(temp, INPUT);


}

/*
  int x;
  double mV;
  double T;
  double ratio = 0.010; 
*/

double analogRead_temp(int pin) {
  return (4.9 * analogRead(pin) - 500) / 10;
}

void loop() {

   // x = 0-1024
   // V = 0.00049x
   // T = V/10*10^-3

  /*
   x = analogRead(temp);

   mV = 4.9 * x - 500; // relative to 0 degree
   T = mV/10;
  */
   
   Serial.println(analogRead_temp(temp));
}
