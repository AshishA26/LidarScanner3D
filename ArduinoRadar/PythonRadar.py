import serial
import time
# make sure the 'COM#' is set according the Windows Device Manager
ser = serial.Serial('COM3', 9600, timeout=1)
time.sleep(2)

for i in range(10000000000):
    line = ser.readline()   # read a byte
    if line:
        string = line.decode()  # convert the byte string to a unicode string
        print(string)

ser.close()
#https://pythonforundergradengineers.com/python-arduino-LED.html#install-pyserial
#https://pythonforundergradengineers.com/python-arduino-potentiometer.html
