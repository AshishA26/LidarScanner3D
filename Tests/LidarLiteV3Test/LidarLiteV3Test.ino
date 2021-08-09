#include <Wire.h>
#include <LIDARLite.h>

// Globals
LIDARLite lidarLite;
int cal_cnt = 0;

void setup()
{
  Serial.begin(9600); // Initialize serial connection to display distance readings

  lidarLite.begin(0, true); // Set configuration to default and I2C to 400 kHz
  lidarLite.configure(0); // Change this number to try out alternate configurations
}

void loop()
{
  int dist;

  // At the beginning of every 100 readings,
  // take a measurement with receiver bias correction
  if ( cal_cnt == 0 ) {
    dist = lidarLite.distance();      // With bias correction
  } else {
    dist = lidarLite.distance(false); // Without bias correction
  }

  // Increment reading counter
  cal_cnt++;
  cal_cnt = cal_cnt % 100;

  // Display distance
  Serial.print(dist);
  Serial.println(" cm");

  delay(10);
}
