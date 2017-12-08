#!/usr/bin/env python
"""

A matplotlib Arduino plot.


"""


import serial
import numpy
import matplotlib.pyplot as plt
from drawnow import *
import time


date_list = []
time_list = []
sensor1 = []
sensor2 = []
sensor3 = []

# Create the serial object to retrieve data from Arduino.
arduino_data = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(4)

# Run matplotlib in interactive mode in order to plot live data.
plt.ion()

counter = 0


def make_figure():
    '''Create the plot to display data.'''
    plt.title("Real-Time Temperature Plot")
    # Enable grid.
    plt.grid(True)
    # Set the Y and X labels.
    plt.ylabel("Fahrenheit")
    plt.xlabel("Seconds")
    # Set the Y axis and X minimum and maximum values.
    plt.ylim(50, 85)
    # Create a red line with circles.
    plt.plot(sensor1, 'ro-', label="sensor1")
    plt.legend(loc='upper left')

    # Create a second Y axis line.
    plt2 = plt.twinx()
    plt.ylim(50, 85)
    # Create a blue line with circles.
    plt2.plot(sensor2, 'bo-', label="sensor2")
    plt.legend(loc='upper center')

    # Create a third Y axis line.
    plt3 = plt.twinx()
    plt.ylim(50, 85)
    # Create a green line with circles.
    plt3.plot(sensor3, 'go-', label="sensor3")
    plt.legend(loc='upper right')


while True:
    while (arduino_data.inWaiting() == 0):
        pass
    
    # Read data from the serial port.
    arduino_string = arduino_data.readline()
    data_array = str(arduino_string).split(',')
    date_list = data_array[0].split('\'')[1]
    t = data_array[1]
    time_list.append(t)
    s1 = float(data_array[2])
    sensor1.append(s1)
    s2 = float(data_array[3])
    sensor2.append(s2)
    s3 = data_array[4].split(" ")
    s3 = float(s3[0])
    sensor3.append(s3)
    drawnow(make_figure)
    plt.pause(.05)
    counter += 1
    # Set the size of the data to be displayed.
    if (counter > 100):
        sensor1.pop(0)
        sensor2.pop(0)
        sensor3.pop(0)
    
