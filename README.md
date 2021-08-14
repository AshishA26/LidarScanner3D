# LidarScanner3D
Made using Arduino and Unreal Engine 4.
### Description
This program and setup that I have created from scratch allows you to create and map a point cloud using LIDAR, Arduino, and Unreal Engine. The angle calculations and many bug fixes have been done to ensure the best performance is there when in use.

## Instructions
- Hook up everything to the arduino based on the ciruit diagrams below
- Depending on the type of LIDAR, upload that code to arduino
- Open the Unreal Engine exe file (found on the releases page), specify com port, baud rate, scan type and go from there

## Help
When trying to load in Unreal Engine 4:
- Remember to rename the .sav file to ScanDataSave.sav
- It goes in \LidarScanner3D\LidarScannerUE4\Saved\SaveGames

When trying to load in the LidarScanner compiled exe:
- Go to .\LidarScannerUE4Compiled\LidarScanner\Saved\SaveGames and find ScanDataSave.sav
- Note: This file has the point cloud data
- If wanted, copy or move it out into a different folder to keep for later and can rename it to something like "room.sav"
- To load back in, name the file as ScanDataSave.sav and move it to the "SaveGames" folder

## Circuit Diagrams (by me)
Circuit Diagram for Lidar Lite V3 (the wiring from the Lite V3 is based on the colors on the diagram):
![ArduinoLidarLiteV3Diagram](https://user-images.githubusercontent.com/44419439/129426226-b9241c6e-dd0b-41c2-91ce-c574880a7d88.png)

Circuit Diagram for TFMini Plus (the wiring from the TFMini Plus is based on the colors on the diagram):
![ArduinoLidarTFMiniDiagram](https://user-images.githubusercontent.com/44419439/129426262-82d0f446-6be1-4c31-97fe-d7f711e6c780.png)

## Scan Pictures
### Using TFMini Plus
![sofa5c](https://user-images.githubusercontent.com/44419439/129427278-67b9fd6d-619c-4f7a-9e68-49b4ab2f010b.png)
![sofa5d](https://user-images.githubusercontent.com/44419439/129427280-5550c4fc-323a-4ab6-beb2-49ee247f7afa.png)
![sofa5e](https://user-images.githubusercontent.com/44419439/129427281-ced7c289-f0f8-4092-92e8-e0e0079b49da.png)

### Using Lidar Lite V3
*Coming Soon*

## Lidar Frame Pictures
![IMG_20210803_111621](https://user-images.githubusercontent.com/44419439/129431828-7d3091e6-1d95-4b54-9bde-9fd300abb350.jpg)
![IMG_20210803_111654](https://user-images.githubusercontent.com/44419439/129431829-83f5ee40-ab1a-4a06-a8d2-78cf1221d6fd.jpg)
