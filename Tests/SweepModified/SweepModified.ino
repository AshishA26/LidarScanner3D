#include <PWMServo.h>

//*************************************************Modified Sweep code*************************************************//
//For testing the servos going 360 degrees
// Include libraries:
#include <Servo.h>
#include<SoftwareSerial.h>
//Create serial object;
SoftwareSerial mySerial(10, 9); //Set Transmit and Recieve pins, pin 2 is RX, pin 3 is TX

Servo servo1;
Servo servo2;

// defines variables
int verAngle = 2000;
long duration;
int distance;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  mySerial.begin(115200);
  servo1.attach(5);
  servo2.attach(6);

  //Tell servo to go to this angle
  servo1.writeMicroseconds(500);
  servo2.writeMicroseconds(verAngle);
  delay(1000);
}

void loop() {
  for (int angle = 500; angle <= 2500; angle += 7)
  {
    servo1.writeMicroseconds(angle);
    Serial.println(angle);
    delay(10);
  }
  MoveUp();
  for (int angle = 2500; angle >= 500; angle -= 7)
  {
    servo1.writeMicroseconds(angle);
    Serial.println(angle);
    delay(10);
  }
  MoveUp();
}
//Move vertical servo up by one degree
void MoveUp() {
  verAngle = verAngle - 7;
  servo2.writeMicroseconds(verAngle);
  delay(10);
}
