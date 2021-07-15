/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
Servo myservo2;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(9);
  myservo.writeMicroseconds(500); 
  myservo2.writeMicroseconds(500); 
  delay(1000);
}

void loop() {
  for (pos = 500; pos <= 2500; pos += 7) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.writeMicroseconds(pos);              // tell servo to go to position in variable 'pos'
    myservo2.writeMicroseconds(pos);              // tell servo to go to position in variable 'pos'
    delay(6);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 2500; pos >= 500; pos -= 7) { // goes from 180 degrees to 0 degrees
    myservo.writeMicroseconds(pos);              // tell servo to go to position in variable 'pos'
    myservo2.writeMicroseconds(pos);              // tell servo to go to position in variable 'pos'
    delay(6);                       // waits 15ms for the servo to reach the position
  }
}
