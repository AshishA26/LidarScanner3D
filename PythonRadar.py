import serial
import time
import numpy as np
import plotly.graph_objects as go

# make sure the 'COM#' is set according the Windows Device Manager
#fig = plt.figure()
#ax = plt.axes(projection="3d")

ser = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)
x_data=[]
y_data=[]
z_data=[]
for i in range(1000):
    line = ser.readline()   # read a byte
    if line:
        string = line.decode()  # convert the byte string to a unicode string
        print(string)
        splitArray = string.split()
        z_point = int(splitArray[1])
        x_point = int(splitArray[0])
        y_point = int(splitArray[2])
#        ax.scatter3D(x_point, y_point, z_point, color="b", cmap='hsv')
        x_data.append(x_point)
        y_data.append(y_point)
        z_data.append(z_point)
marker_data = go.Scatter3d(
    x=x_data[:], 
    y=y_data[:], 
    z=z_data[:],
    marker=go.scatter3d.Marker(size=3), 
    opacity=0.8, 
    mode='markers'
)
        
ser.close()
#plt.xlabel('x')
#plt.ylabel('y')


#plt.title('Sonar Scan')
#plt.show()


fig=go.Figure(data=marker_data)
fig.show()

#https://pythonforundergradengineers.com/python-arduino-LED.html#install-pyserial
#https://pythonforundergradengineers.com/python-arduino-potentiometer.html
#https://towardsdatascience.com/an-easy-introduction-to-3d-plotting-with-matplotlib-801561999725
#https://stackoverflow.com/questions/43187484/matplotlib-slow-3d-scatter-rotation