import serial
import time
import numpy as np
import plotly.graph_objects as go
import math

# make sure the 'COM#' is set according the Windows Device Manager
#fig = plt.figure()
#ax = plt.axes(projection="3d")

ser = serial.Serial('COM3', 115200, timeout=1)
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
        
        thetaDEG = int(splitArray[0])
        thetaRAD = thetaDEG * math.pi / 180
        alphaDEG = int(splitArray[1])
        alphaRAD = alphaDEG * math.pi / 180
        r = int(splitArray[2])

        z_point = r * math.sin(alphaRAD)
        x_point = r * math.cos(alphaRAD) * math.cos(thetaRAD)
        y_point = r * math.cos(alphaRAD) * math.sin(thetaRAD)

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
# fig.update_layout(
#     scene = dict(
#         xaxis = dict(nticks=10, range=[0,5000],),
#                      yaxis = dict(nticks=10, range=[0,5000],),
#                      zaxis = dict(nticks=10, range=[0,5000],),),
#     width=700,
#     margin=dict(r=20, l=10, b=10, t=10))
fig.show()

#https://pythonforundergradengineers.com/python-arduino-LED.html#install-pyserial
#https://pythonforundergradengineers.com/python-arduino-potentiometer.html
#https://towardsdatascience.com/an-easy-introduction-to-3d-plotting-with-matplotlib-801561999725
#https://stackoverflow.com/questions/43187484/matplotlib-slow-3d-scatter-rotation
#https://plotly.com/python/3d-axes/


# import pickle
 
# f = open('parrot.pkl', 'wb')
# pickle.dump(x_data, f)

# f.close()