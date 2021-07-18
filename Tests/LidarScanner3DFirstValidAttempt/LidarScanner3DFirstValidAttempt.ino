//#include <PWMServo.h>

//*************************************************3D RADAR CODE*************************************************//

//************************************************************************//

// Include libraries:
#include <Servo.h>

// Create a new servo object:
Servo servo1;
Servo servo2;
//PWMServo servo1;
//PWMServo servo2;

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
int angle = 600;
int verAngle = 2000;
long duration;
int distance;
int pointArray[3];
int mapAngle;
int mapVerAngle;
int mapStartVerAngle;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  Serial3.begin(115200);
 // Serial.print("start");

  // Attach the Servo variable to a pin:
  servo1.attach(9);
  servo2.attach(10);

  //Tell servo to go to this angle
  servo1.writeMicroseconds(angle);
  servo2.writeMicroseconds(verAngle);
  pointArray[0] = 0;

  mapStartVerAngle = verAngle;
  mapStartVerAngle = map(mapStartVerAngle, 500, 2500, -90, 180);

  pointArray[1] = mapStartVerAngle;
  delay(1000);
}

void loop() {
  // Sweep from 0 to 2500 degrees:
  for (angle = 600; angle <= 2400; angle += 7)
  {
    Sonar();
    mapAngle = angle;
    mapAngle = map(mapAngle, 500, 2500, 0, 270);
    printArray();
    pointArray[0] = mapAngle;
    servo1.writeMicroseconds(angle);
    delay(10);
  }
  MoveUp();
  // And back from 2500 to 0 degrees:
  for (angle = 2400; angle >= 600; angle -= 7)
  {
    Sonar();
    mapAngle = angle;
    mapAngle = map(mapAngle, 500, 2500, 0, 270);
    printArray();
    pointArray[0] = mapAngle;
    servo1.writeMicroseconds(angle);
    delay(10);
  }
  MoveUp();
}
//Move vertical servo up by one degree
void MoveUp() {
  if (verAngle >=1000) {
    verAngle = verAngle - 7;
    servo2.writeMicroseconds(verAngle);
    mapVerAngle = verAngle;
    mapVerAngle = map(mapVerAngle, 500, 2500, -90, 180);
    pointArray[1] = mapVerAngle;
    delay(10);
  }
}

void Sonar() {
  if (Serial3.available()) {
    if (Serial3.read() == HEADER) {
      uart[0] = HEADER;
      if (Serial3.read() == HEADER) {
        uart[1] = HEADER;
        for (i = 2; i < 9; i++) {
          uart[i] = Serial3.read();
        }
        check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
        if (uart[8] == (check & 0xff)) {
          dist = uart[2] + uart[3] * 256;
          strength = uart[4] + uart[5] * 256;
//          Serial.print(dist);
//          Serial.print('\n');
          pointArray[2] = dist;
          delay(10);
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
