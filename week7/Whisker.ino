/*
 * Robotics with the BOE Shield - DisplayWhiskerStates
 * Display left and right whisker states in Serial Monitor.
 * 1 indicates no contact; 0 indicates contact.
 */

void setup()                                 // Built-in initialization block
{
  tone(4, 3000, 1000);                       // Play tone for 1 second
  delay(1000);                               // Delay to finish tone
  pinMode(7, INPUT);                         // Set right whisker pin to input
  pinMode(5, INPUT);                         // Set left whisker pin to input  
  //servoLeft.attach(13);  // Attach left signal to pin 13
 // servoRight.attach(12); // Attach right signal to pin 12
  
  Serial.begin(9600);                        // Set data rate to 9600 bps
}  
 
void loop()                                  // Main loop auto-repeats
{                                            
  byte wLeft = digitalRead(5);               // Copy left result to wLeft  
  byte wRight = digitalRead(7);              // Copy right result to wRight
  //servoLeft.writeMicroseconds(1700);  // Left wheel counterclockwise
  //servoRight.writeMicroseconds(1300); // Right wheel clockwise
  
  Serial.print(wLeft);                       // Display left whisker state
  Serial.println(wRight);                    // Display right whisker state

  delay(50);                                 // Pause for 50 ms
}    
