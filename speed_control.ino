#include <Servo.h>                                // Include servo library

Servo servoLeft;                                  // Declare left and right
                                                  // servos
Servo servoRight;

void setup()                                      // Initialization block
{
    servoLeft.attach(13);                         // Left signal to pin 13
    servoRight.attach(12);                        // Right signal to pin 12
    for(int speed = 0; speed <= 200; speed += 10) // Ramp up to full speed.
    {
        servoLeft.writeMicroseconds(1500+speed);  // us = 1500,1510,... 1700
        servoRight.writeMicroseconds(1500-speed); // us = 1500,1490,... 1300
        delay(500);                               // 500 ms at each speed
    }
    delay(1000);                                  // Full speed for 2 seconds
    servoLeft.detach();                           // Stop sending servo signal
    servoRight.detach();
 }

 void loop()                                      // Main loop auto-repeats
 {                                                // Empty, nothing to repeat
 }
