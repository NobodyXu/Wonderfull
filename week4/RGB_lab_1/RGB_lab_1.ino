#define red 9
#define green 10
#define blue 11

void setup() {
  Serial.begin(9600);
  pinMode(red, OUTPUT); 
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

struct rgb {
  int r;
  int g;
  int b;
};

rgb rainbows[] = {rgb{255, 0, 0}, // red
                  rgb{255, 165, 0}, // Orange
                  rgb{255, 255, 0}, // Yellow
                  rgb{0, 128, 0}, // Green
                  rgb{0, 0, 255}, // Blue
                  rgb{128, 0, 128}, // Purple
                  rgb{75, 0, 130} // Indigo
                  };

void loop() {
   analogWrite(red, 0);
   analogWrite(blue, 0);
   analogWrite(green, 0);

   int i = 0;
   while (i < 7) {
      analogWrite(red, rainbows[i].r);
      analogWrite(green, rainbows[i].g);
      analogWrite(blue, rainbows[i].b);
    
      ++i;
      delay(1000);
   }

   analogWrite(red, 0);
   analogWrite(blue, 0);
   analogWrite(green, 0);

   delay(5000);
   
   

}
