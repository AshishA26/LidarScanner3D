import serial
import time
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import numpy as np

# make sure the 'COM#' is set according the Windows Device Manager
fig = plt.figure()
ax = plt.axes(projection="3d")

ser = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)

for i in range(100):
    line = ser.readline()   # read a byte
    if line:
        string = line.decode()  # convert the byte string to a unicode string
        print(string)
        splitArray = string.split()
        z_point = int(splitArray[1])
        x_point = int(splitArray[0])
        y_point = int(splitArray[2])
        z_points = z_point
        x_points = x_point
        y_points = y_point
        ax.scatter3D(x_points, y_points, z_points, color="b", cmap='hsv')
        
ser.close()
plt.xlabel('x')
plt.ylabel('y')


plt.title('Sonar Scan')
plt.show()

#https://pythonforundergradengineers.com/python-arduino-LED.html#install-pyserial
#https://pythonforundergradengineers.com/python-arduino-potentiometer.html
#https://towardsdatascience.com/an-easy-introduction-to-3d-plotting-with-matplotlib-801561999725