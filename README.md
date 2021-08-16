# LidarScanner3D
Made using Arduino and Unreal Engine 4.

*Compiled exe is available in the releases of this repository.*

This program and setup that I have created from scratch allows you to create and map a point cloud using LIDAR, Arduino, and Unreal Engine. The real time visualization tool was made in Unreal Engine, and the LIDAR interfaced with the Arduino Mega using UART and I2C communication protocol. The angle calculations and many bug fixes have been done to ensure the best performance is there when in use.

## Instructions
- Hook up everything to the arduino based on the ciruit diagrams below
- Depending on the type of LIDAR, upload that code to arduino
- Run the Unreal Engine .exe file , specify com port, baud rate, scan type and go from there

## Help
When trying to load in Unreal Engine 4:
- Remember to rename the .sav file to ScanDataSave.sav
- It goes in .\LidarScanner3D\LidarScannerUE4\Saved\SaveGames

When trying to load in the LidarScanner compiled .exe file:
- Go to .\LidarScannerUE4Compiled\LidarScanner\Saved\SaveGames and find ScanDataSave.sav
- Note: This file has the point cloud data
- If wanted, copy or move it out into a different folder to keep for later and can rename it to something like "room.sav"
- To load back in, name the file as ScanDataSave.sav and move it to the "SaveGames" folder

## Circuit Diagrams (made by me using Fritzing)
Circuit Diagram for Lidar Lite V3 (the wiring from the Lite V3 is based on the colors in the diagram):
![ArduinoLidarLiteV3Diagram](https://user-images.githubusercontent.com/44419439/129426226-b9241c6e-dd0b-41c2-91ce-c574880a7d88.png)

Circuit Diagram for TFMini Plus (the wiring from the TFMini Plus is based on the colors in the diagram):
![ArduinoLidarTFMiniDiagram](https://user-images.githubusercontent.com/44419439/129426262-82d0f446-6be1-4c31-97fe-d7f711e6c780.png)

## Scan Pictures
### Using TFMini Plus:
![sofa5c](https://user-images.githubusercontent.com/44419439/129427278-67b9fd6d-619c-4f7a-9e68-49b4ab2f010b.png)
![sofa5d](https://user-images.githubusercontent.com/44419439/129427280-5550c4fc-323a-4ab6-beb2-49ee247f7afa.png)
![sofa5e](https://user-images.githubusercontent.com/44419439/129427281-ced7c289-f0f8-4092-92e8-e0e0079b49da.png)

### Using Lidar Lite V3:
![sofaLiteV3d](https://user-images.githubusercontent.com/44419439/129435652-80d78f99-d1dd-4499-afa8-33a7493f6a58.png)![sofaLiteV3a](https://user-images.githubusercontent.com/44419439/129435653-24178754-fbf7-4407-9de5-917243b70714.png)
![sofaLiteV3c](https://user-images.githubusercontent.com/44419439/129435655-1f7691a0-1eae-4c95-998a-8fab4911a48f.png)

## The Making Story

When I started this project, my initial idea was to get a 2D radar working which would use one servo, one ultrasonic sonar, and an arduino, and that would be it. But then, I got a better idea of making a 3D Radar which would create point clouds and map out objects. The first thing I tried to do was use a sonar, 2 of the basic small servos (like these https://www.amazon.ca/Miuzei-Helicopter-Airplane-Remote-Control/dp/B07H85M78M/ref=sr_1_1_sspa), and a wooden block. I would need 2 servos so that one could allow horizontal turning, and one the allows verical scanning. 

I started with a wooden block and attached the servo to it on its side using a strip of metal pipe hanger. Then I put a piece of flexible aluminum ontop of the servo so that I could attach the 2nd servo for vertical turning. Then I bent another piece of flexible aluminum to hold the sonar in place and got the whole set up put together. 

*Insert Pic here*

I then did the angle calculations for finding the exact location of the point relative to the ultrasonic sonar.

![PointCalculation](https://user-images.githubusercontent.com/44419439/129597812-3d379170-6a0e-4b6f-a8df-65af5eb2bd27.jpg)

When I went to test out my code, I encountered a problem: the makeshift frame I had built was very unstable.

I had an idea of making an solid aluminum frame, which I felt would be very stable. In order to be able to support the load and to have more stability, I needed to get new servos, and so I got these https://www.amazon.ca/product-reviews//B07RFRLRV8/ref=acr_dpx_hist_1 which would be able to support more load. This aluminum frame was hand built and designed by me. It allows for easy portability and rotation.

![IMG_20210803_111654](https://user-images.githubusercontent.com/44419439/129431829-83f5ee40-ab1a-4a06-a8d2-78cf1221d6fd.jpg)
![IMG_20210803_111621](https://user-images.githubusercontent.com/44419439/129431828-7d3091e6-1d95-4b54-9bde-9fd300abb350.jpg)

Now with the frame stable, it was time to test it out and see how it worked. I made the code in Arduino, and the plotting was made in Python and was going to use MatPlotLib to visualize the point cloud.

It was here I encountered 3 problems:
1. The sonar was not giving accurate results at all and had way too much noise
2. MatPlotLib was had a very high latency (laggy)
3. And the biggest problem was that the servos were jittering a lot, and sometimes continously turning 360 degrees when the servos aren't even programmed to do so

### Problem #1
### Problem #2
### Problem #3
