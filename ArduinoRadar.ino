//*************************************************3D RADAR CODE*************************************************//

// Include libraries:
#include <Servo.h>
#include<SoftwareSerial.h>
//Create serial object;
SoftwareSerial mySerial(10, 9); //Set Transmit and Recieve pins, pin 2 is RX, pin 3 is TX
// Create a new servo object:
Servo servo1;
Servo servo2;


// Define the servo pin:
//int servo1Pin = 9;
//int servo2Pin = 10; THESE WERE SOMEHOW CAUSING THE PROBLEM OF THE 2 BIG SERVOS NOT TO WORK, ONLY ONE OF THEM HAD WORKED

int dist;
int strength;
int check;
int uart[9];
int i;
const int HEADER = 0x59;

// defines variables
int angle = 500;
int verAngle = 2000;
long duration;
int distance;
int pointArray[3];
int mapAngle;
int mapVerAngle;
int mapStartVerAngle;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  mySerial.begin(115200);
  Serial.print("start");

  // Attach the Servo variable to a pin:
  servo1.attach(5);
  servo2.attach(6);

  //Tell servo to go to this angle
  servo1.writeMicroseconds(angle);
  servo2.writeMicroseconds(verAngle);
  pointArray[0] = 0;

  mapStartVerAngle = verAngle;
  mapStartVerAngle = map(mapStartVerAngle, 500, 2500, 0, 180);

  pointArray[1] = mapStartVerAngle;
  delay(1000);
}

void loop() {
  // Sweep from 0 to 2500 degrees:
  for (angle = 500; angle <= 2500; angle += 5)
  {
    Sonar();
    mapAngle = angle;
    mapAngle = map(mapAngle, 500, 2500, 0, 180);
    printArray();
    pointArray[0] = mapAngle;
    servo1.writeMicroseconds(angle);
    delay(10);
  }
  MoveUp();
  // And back from 2500 to 0 degrees:
  for (angle = 2500; angle >= 500; angle -= 5)
  {
    Sonar();
    mapAngle = angle;
    mapAngle = map(mapAngle, 500, 2500, 0, 180);
    printArray();
    pointArray[0] = mapAngle;
    servo1.writeMicroseconds(angle);
    delay(10);
  }
  MoveUp();
}
//Move vertical servo up by one degree
void MoveUp() {
  verAngle = verAngle - 5;
  servo2.writeMicroseconds(verAngle);
  mapVerAngle = verAngle;
  mapVerAngle = map(mapVerAngle, 500, 2500, 0, 180);
  pointArray[1] = mapVerAngle;
  delay(10);
}

void Sonar() {
  if (mySerial.available()) {
    if (mySerial.read() == HEADER) {
      uart[0] = HEADER;
      if (mySerial.read() == HEADER) {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) {
          uart[i] = mySerial.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff)) {
          dist = uart[2] + uart[3] * 256;
          strength = uart[4] + uart[5] * 256;
          Serial.print(dist);
          Serial.print('\n');
          delay(0);
          pointArray[2] = dist;
        }
      }
    }
  }
}

void printArray() {
  for (int i = 0; i < 3; i++) {
    Serial.print(pointArray[i]);
    if (i != 2) {
      Serial.print(" ");
    }
  }
  Serial.println();
}
