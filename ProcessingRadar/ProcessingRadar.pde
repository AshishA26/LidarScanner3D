import peasy.*;
import processing.serial.*;    // Importing the serial library to communicate with the Arduino 
 
PeasyCam cam;
Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port
String[] sa1 = {}; 

void setup() {
  size(500,500,P3D);
  cam = new PeasyCam(this, 500);
  cam.setMinimumDistance(100);
  cam.setMaximumDistance(1000);
  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
}

void draw() { 
 
  color blue = color (0,0,255);
  color yellow = color (255,255,0);
 
  rotateX(-.001);
  rotateY(-.001);
  background(255);
  translate(0,0,0);
 
  pushMatrix();
    fill(200);
  rect(0,0,125,125);
 
  // axis x
  stroke(0,100,0); 
  line(0, 0, 0, 150, 0, 0);
  fill(0,100,0);
  text("X Axis",140,-5,0);
 
  stroke(200);
  line(0, 0, 10, 100, 0, 10);
  line(0, 0, 20, 100, 0, 20);
  line(0, 0, 30, 100, 0, 30);
  line(0, 0, 40, 100, 0, 40);
  line(0, 0, 50, 100, 0, 50);
 
 
  stroke(255,0,0);
  line(0, 0, 0, 0, 150, 0);
 
  pushMatrix();
  rotate(-HALF_PI);
  fill(255,0,0);
  text("Y Axis",-160,-5,0);
  popMatrix();
 
 
 
  stroke(200);
  line(0, 0, 10, 0, 100, 10);
  line(0, 0, 20, 0, 100, 20);
  line(0, 0, 30, 0, 100, 30);
  line(0, 0, 40, 0, 100, 40);
  line(0, 0, 50, 0, 100, 50);
 
 
 
 
 
stroke(0,0,255);
line(0, 0, 0, 0, 0, 150);
pushMatrix();
  rotateY(-HALF_PI);
  fill(0,0,255);
  text("Z Axis",140,-5,0);
  popMatrix();
 
 
 
stroke(200);
line(10, 0, 0, 10, 0, 100);
line(20, 0, 0, 20, 0, 100);
line(30, 0, 0, 30, 0, 100);
line(40, 0, 0, 40, 0, 100);
line(50, 0, 0, 50, 0, 100);
line(0, 10, 0, 0, 10, 100);
line(0, 20, 0, 0, 20, 100);
line(0, 30, 0, 0, 30, 100);
line(0, 40, 0, 0, 40, 100);
line(0, 50, 0, 0, 50, 100);
  
  
  
  
  for (int i = 0; i < 1000; i = i+1) {
    if ( myPort.available() > 0) 
    {  // If data is available,
      val = myPort.readStringUntil('\n');         // read it and store it in val
      println(val); //print it out in the console
      
      //String[] splitArray = split(val, ' ');
      //int x_point = Integer.valueOf(splitArray[0]);
      //int y_point = Integer.valueOf(splitArray[1]);
      //int z_point = Integer.valueOf(splitArray[2]);
      
      //translate(x_point, y_point, z_point);
      //noStroke();
      //lights();
      //fill(0,255,0);
      //sphere(5);
    } 
  }

 
 
translate(10, 10, 10);
noStroke();
lights();
fill(0,255,0);
sphere(5);
 
 
translate(25, 10, 50);
noStroke();
lights();
fill(blue);
sphere(5);
 
translate(25, 30, 10);
noStroke();
lights();
fill(255,0,0);
sphere(5);
 
translate(75, 10, 50);
noStroke();
lights();
fill(yellow);
sphere(5);
 
translate(0,0,50);
popMatrix();
 
//printCamera();
}
