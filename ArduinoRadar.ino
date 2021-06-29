//*************************************************Radar code*************************************************//

// Include the servo library:
#include <Servo.h>
// Create a new servo object:
Servo servo1;
Servo servo2;

// Define the servo pin:
//int servo1Pin = 9;
//int servo2Pin = 10; THESE WERE SOMEHOW CAUSING THE PROBLEM OF THE 2 BIG SERVOS NOT TO WORK, ONLY ONE OF THEM HAD WORKED

// defines pins numbers
const int trigPin = 6;
const int echoPin = 7;

// defines variables
int angle = 800;
int verAngle = 1500;
long duration;
int distance;
int pointArray[3];
int mapAngle;
int mapVerAngle;
int mapStartVerAngle;

void setup()
{
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
    Serial.begin(9600);       // Starts the serial communication

    // Attach the Servo variable to a pin:
    servo1.attach(9);
    servo2.attach(10);

    //Tell servo to go to this angle
    servo1.writeMicroseconds(angle);
    servo2.writeMicroseconds(verAngle);
    pointArray[0] = 0;

        mapStartVerAngle = verAngle;
        mapStartVerAngle = map(mapStartVerAngle, 500, 2500, 0, 180); 
    
    pointArray[1] = mapStartVerAngle;
    delay(1000);
}

void loop()
{
  if (verAngle>1000) {
    // Sweep from 0 to 2500 degrees:
    for (angle = 800; angle <= 2200; angle += 5)
    {
        Sonar();
        mapAngle = angle;
        mapAngle = map(mapAngle, 500, 2500, 0, 180); 
        printArray();
        pointArray[0] = mapAngle;
        servo1.writeMicroseconds(angle);
        delay(0);
    }
    MoveUp();
    // And back from 2500 to 0 degrees:
    for (angle = 2200; angle >= 800; angle -= 5)
    {
        Sonar();
        mapAngle = angle;
        mapAngle = map(mapAngle, 500, 2500, 0, 180);
        printArray();
        pointArray[0] = mapAngle;
        servo1.writeMicroseconds(angle);
        delay(0);
    }
    MoveUp();
  }
  else {
    Serial.println("End");
  }
}
//Move vertical servo up by one degree
void MoveUp()
{
    verAngle = verAngle - 5;
    servo2.writeMicroseconds(verAngle);
    mapVerAngle = verAngle;
    mapVerAngle = map(mapVerAngle, 500, 2500, 0, 180); 
    pointArray[1] = mapVerAngle;
    delay(10);
}

void Sonar()
{
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
//    Serial.print("Distance: ");
//    Serial.println(distance);
    pointArray[2] = distance;
}

void printArray()
{
      //  Serial.print("[");
        for(int i = 0; i < 3; i++)
        {
        
          Serial.print(pointArray[i]);
          if (i!=2) {
            Serial.print(" ");
            }
        }
      //  Serial.print("]");
        Serial.println();
}
