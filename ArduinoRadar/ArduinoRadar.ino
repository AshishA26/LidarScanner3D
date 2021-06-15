//*************************************************Radar code*************************************************//

// Include the servo library:
#include <Servo.h>
// Create a new servo object:
Servo servo1;
Servo servo2;
// Define the servo pin:
int servo1Pin = 9;
int servo2Pin = 10;

// defines pins numbers
const int trigPin = 6;
const int echoPin = 7;

// defines variables
int angle = 0;
int verAngle = 180;
long duration;
int distance;
int pointArray[3];

void setup()
{
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
    Serial.begin(9600);       // Starts the serial communication

    // Attach the Servo variable to a pin:
    servo1.attach(servo1Pin);
    servo2.attach(servo2Pin);

    //Tell servo to go to this angle
    servo1.write(0);
    servo2.write(180);
    pointArray[1] = 180;
    delay(1000);
}

void loop()
{
    // Sweep from 0 to 180 degrees:
    for (angle = 0; angle <= 180; angle += 1)
    {
        Sonar();
        printArray();
//        Serial.print("HorizonAngle: ");
//        Serial.println(angle);
        pointArray[0] = angle;
        servo1.write(angle);
        delay(10);
    }
    MoveUp();
    // And back from 180 to 0 degrees:
    for (angle = 180; angle >= 0; angle -= 1)
    {
        Sonar();
        printArray();
//        Serial.print("HorizonAngle: ");
//        Serial.println(angle);
        pointArray[0] = angle;
        servo1.write(angle);
        delay(10);
    }
    MoveUp();
}
//Move vertical servo up by one degree
void MoveUp()
{
//    Serial.print("verAngle: ");
//    Serial.println(verAngle);
    pointArray[1] = verAngle;
    servo2.write(verAngle);
    verAngle = verAngle - 10;
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
