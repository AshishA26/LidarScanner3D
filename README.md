# ArduinoRadar
Made using Arduino and Unreal Engine 4.

## Notes
When trying to load in Unreal Engine 4:
- Remember to rename the .sav file to ScanDataSave.sav
- It goes in \LidarScanner3D\LidarScannerUE4\Saved\SaveGames

When trying to load in the LidarScanner compiled exe:
- Go to .\LidarScannerUE4Compiled\LidarScanner\Saved\SaveGames and find ScanDataSave.sav
- This file has the point cloud data
- If wanted, copy or move it out into a different folder to keep for later and can rename it to something like "room.sav"
- To load back in, name the file as ScanDataSave.sav and move it to the "SaveGames" folder