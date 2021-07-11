// LidarScanner.ino Arduino sketch
// http://www.qcontinuum.org/lidar

// Load sketch into Arduino software, available from:
// https://www.arduino.cc/

// This sketch controls X and Y servos to pan/tilt a LIDAR detector,
// either manually (by pressing LCD buttons to control XY location),
// or automatically (scanning horizontally and vertically).
// XYZ coordinates are output to the serial port to be received and
// displayed on computer by LidarScanner.pde Processing sketch.

// This sketch requires library "LIDAR-Lite v3" by Garmin.
// Select menu "Sketch", "Include Library", "Manage Libraries...",
// and in textbox "Filter your search...", enter "lidar".

// Freetronics LCD shield uses D3 to control backlight brightness,
// but digital output needed for servo control, so disable the
// backlight control by cutting strap marked "D3" on LCD shield.

#include <Servo.h>
#include <LIDARLite.h>
#include <LiquidCrystal.h>

Servo servoX;
Servo servoY;
LIDARLite lidar;
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Minimum and maximum servo angle in degrees
// Modify to avoid hitting limits imposed by pan/tilt bracket geometry
int minPosX = 0;
int maxPosX = 180;
int minPosY = 26;
int maxPosY = 125;

int buttonPin = A0;
int buttonValue = 0;
int buttonThreshold = 50;
int lastPosX = 0;
int lastPosY = 0;
int loopCount = 0;
int radius = 0;
int lastRadius = 0;
boolean selectButtonPressed = false;
boolean scanning = false;
boolean scanDirection = false;
int scanIncrement = 1;
int posX = (maxPosX + minPosX) / 2;
int posY = (maxPosY + minPosY) / 4;
float pi = 3.14159265;
float deg2rad = pi / 180.0;

void setup() {
  lcd.begin(16, 2);
  updateModeDisplay();
  lidar.begin(0, true);
  lidar.configure(0);
  servoX.attach(2);
  servoY.attach(3);
  servoX.write(posX);
  servoY.write(posY);
  Serial.begin(9600);
}

void loop() {

  buttonValue = analogRead(buttonPin);

  if (scanning) {
    if (abs(buttonValue - 741) < buttonThreshold) {
      if (!selectButtonPressed) {
        // switch to manual scan mode
        selectButtonPressed = true;
        scanning = false;
        updateModeDisplay();
      }
    } else {
      selectButtonPressed = false;
    }
    if (scanDirection) {
      posX += scanIncrement;
    } else {
      posX -= scanIncrement;
    }
    if (posX > maxPosX || posX < minPosX) {
      // hit limit X limit, reverse auto scan direction
      scanDirection = !scanDirection;
      posY += scanIncrement;
      if (posY > maxPosY) {
        // completed auto scan, return to manual scan mode
        scanning = false;
        updateModeDisplay();
      }
    }
  } else {
    if (abs(buttonValue - 741) < buttonThreshold) {
      if (!selectButtonPressed) {
        // switch to auto scan mode
        selectButtonPressed = true;
        scanning = true;
        posX = minPosX;
        posY = minPosY;
        scanDirection = true;
        updateModeDisplay();
      }
    } else if (abs(buttonValue - 505) < buttonThreshold) {
      // manual scan left
      posX += 1;
    } else if (abs(buttonValue - 329) < buttonThreshold) {
      // manual scan down
      posY -= 1;
    } else if (abs(buttonValue - 145) < buttonThreshold) {
      // manual scan up
      posY += 1;
    } else if (abs(buttonValue - 0) < buttonThreshold) {
      // manual scan right
      posX -= 1;
    } else {
      selectButtonPressed = false;
    }
  }

  posX = min(max(posX, minPosX), maxPosX);
  posY = min(max(posY, minPosY), maxPosY);
  bool moved = moveServos();
  displayPosition();

  loopCount += 1;
  if (loopCount % 100 == 0) {
    // recalibrate scanner every 100 scans
    radius = lidar.distance();
  } else {
    radius = lidar.distance(false);
  }
  if (abs(radius - lastRadius) > 2)
  {
    lastRadius = radius;
    lcd.setCursor(8, 0);
    lcd.print("D:" + String(radius / 100.0, 2) + "  ");
  }
  if (scanning || moved) {
    float azimuth = posX * deg2rad;
    float elevation = (180 - maxPosY + posY) * deg2rad;
    double x = radius * sin(elevation) * cos(azimuth);
    double y = radius * sin(elevation) * sin(azimuth);
    double z = radius * cos(elevation);
    Serial.println(String(-x, 5) + " " + String(y, 5) + " " + String(-z, 5));
  }
}

bool moveServos()
{
  bool moved = false;
  static int lastPosX;
  static int lastPosY;
  int delta = 0;  
  if (posX != lastPosX) {
    delta += abs(posX - lastPosX);
    servoX.write(posX);
    lastPosX = posX;
    moved = true;
  }
  if (posY != lastPosY) {
    delta += abs(posY - lastPosY);
    servoY.write(posY);
    lastPosY = posY;
    moved = true;
  }
  delay(30);
  return moved;
}

void displayPosition()
{
  static int lastPosX;
  static int lastPosY;
  if (posX != lastPosX) {
    lcd.setCursor(0, 0);
    lcd.print("X:" + String(posX) + "  ");
    lastPosX = posX;
  }
  if (posY != lastPosY) {
    lcd.setCursor(0, 1);
    lcd.print("Y:" + String(posY) + "  ");
    lastPosY = posY;
  }  
}

void updateModeDisplay()
{
  lcd.setCursor(8, 1);
  if (scanning) {
    lcd.print("Scanning");
  } else {
    lcd.print("Manual  ");
  }
}

