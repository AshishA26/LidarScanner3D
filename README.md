# ArduinoRadar
Made using Arduino and Unreal Engine 4.

## Instructions
- Hook up everything to the arduino based on the ciruit diagrams below
- Depending on the type of LIDAR, upload that code to arduino
- Open the Unreal Engine exe file (found on the releases page), specify com port, baud rate, scan type and go from there

## Notes
When trying to load in Unreal Engine 4:
- Remember to rename the .sav file to ScanDataSave.sav
- It goes in \LidarScanner3D\LidarScannerUE4\Saved\SaveGames

When trying to load in the LidarScanner compiled exe:
- Go to .\LidarScannerUE4Compiled\LidarScanner\Saved\SaveGames and find ScanDataSave.sav
- This file has the point cloud data
- If wanted, copy or move it out into a different folder to keep for later and can rename it to something like "room.sav"
- To load back in, name the file as ScanDataSave.sav and move it to the "SaveGames" folder

## Circuit Diagrams
Circuit Diagram for Lidar Lite V3 (the wiring from the Lite V3 is based on the colors on the diagram):
![ArduinoLidarLiteV3Diagram](https://user-images.githubusercontent.com/44419439/129426226-b9241c6e-dd0b-41c2-91ce-c574880a7d88.png)

Circuit Diagram for TFMini Plus (the wiring from the TFMini Plus is based on the colors on the diagram):
![ArduinoLidarTFMiniDiagram](https://user-images.githubusercontent.com/44419439/129426262-82d0f446-6be1-4c31-97fe-d7f711e6c780.png)
