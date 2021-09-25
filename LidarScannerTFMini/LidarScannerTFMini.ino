//*************************************************3D RADAR CODE with TFMINI PLUS*************************************************//
// By Ashish Agrahari
// https://github.com/AshishA26
//************************************************************************//

// Include libraries:
#include <Servo.h>

// Create a new servo object:
Servo servo1;
Servo servo2;

int dist;
int strength;
int check;
int uart[9];
int i;
const int HEADER = 0x59;
#define LIDAR_MIN_DIST 0
#define LIDAR_MAX_DIST 1200 // in cm
#define SAMPLES 5

// This value changes the ranges and everything
String scanType = "Nothing"; // say either room or sofa

// defines variables
int angle; // For short scan, I did 1350, for room 600, for sofa 1150
int verAngle; // For short scan I did 1850, for room 1900, or 1800, for sofa 2000
int verAngleStop; //For short scan I did 1500, for room 1150, for sofa 1550
int angleFrom; // for short scan, I did 1350, for room 600, for sofa 1150
int angleTo; // for short scan, I did 1700, for room 2400, for sofa 1900

int horizonDelay = 50;
long duration;
int distance;
int pointArray[3];
int mapAngle;
int mapVerAngle;
int mapStartVerAngle;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  Serial3.begin(115200);

  // Attach the Servo variable to a pin:
  servo1.attach(9);
  servo2.attach(10);

  // Gets the scan type from unreal engine
  while (scanType.equals("Nothing") || scanType.equals("")) {
    scanType = Serial.readString();
  }
  scanType.trim(); //Removes white space

  // Changes values and ranges based on the scan type
  if (scanType.equals("sofa")) {
    angle = 1150;
    verAngle = 2000;
    verAngleStop = 1550;
    angleFrom = 1150;
    angleTo = 1900;
  }
  else if (scanType.equals("room")) {
    angle = 600;
    verAngle = 1900; // or 1800
    verAngleStop = 1150;
    angleFrom = 600;
    angleTo = 2400;
  }
  else {
    Serial.println("No scan type set, please retry");
  }
  
  //Tell servo to go to this angle
  servo1.writeMicroseconds(angle);
  servo2.writeMicroseconds(verAngle);
  pointArray[0] = 0;

  // Sends correct mapped angle to serial
  mapStartVerAngle = verAngle;
  mapStartVerAngle = map(mapStartVerAngle, 500, 2500, 180, -90);
  pointArray[1] = mapStartVerAngle;
  for (int i = 0; i < 5; i = i + 1) {
    Serial.print(scanType);
    delay(1000);
  }
}

void loop() {
  // Sweep from 0 to 2500 degrees:
  if (verAngle >= verAngleStop) {

    for (angle = angleFrom; angle <= angleTo; angle += 7)
    {
      pointArray[2] = SmoothLidarReading();
      mapAngle = angle;
      mapAngle = map(mapAngle, 500, 2500, 0, 270);
      printArray();
      pointArray[0] = mapAngle;
      servo1.writeMicroseconds(angle);
      delay(horizonDelay);
    }
    MoveUp();
    // And back from 2500 to 0 degrees:
    for (angle = angleTo; angle >= angleFrom; angle -= 7)
    {
      pointArray[2] = SmoothLidarReading();
      mapAngle = angle;
      mapAngle = map(mapAngle, 500, 2500, 0, 270);
      printArray();
      pointArray[0] = mapAngle;
      servo1.writeMicroseconds(angle);
      delay(horizonDelay);
    }
    MoveUp();
  }
}
//Move vertical servo up by one degree
void MoveUp() {
  if (verAngle >= verAngleStop) {
    verAngle = verAngle - 7;
    servo2.writeMicroseconds(verAngle);
    mapVerAngle = verAngle;
    mapVerAngle = map(mapVerAngle, 500, 2500, 180, -90);
    pointArray[1] = mapVerAngle;
    delay(20);
  }
}

int LidarReading() {
  // Returns distance in centimeters
  if (Serial3.available()>=9) { // >=9 is very important to make sure it has all 9 bytes for UART to work, otherwise it would return -1 and the calculations would be wrong.
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
          //strength = uart[4] + uart[5] * 256;
          return dist;

        }
      }
    }
  }
  delay(10);
  return -1;
}

float SmoothLidarReading() {
  float averageDist = 0;
  for (int i = 0; i < SAMPLES; i = i + 1) {
    int x = float(LidarReading());
    while (x < LIDAR_MIN_DIST || x > LIDAR_MAX_DIST) {
      x = float(LidarReading());
    }
    averageDist = averageDist + x;
  }
  averageDist = averageDist / SAMPLES;
  return averageDist;
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
