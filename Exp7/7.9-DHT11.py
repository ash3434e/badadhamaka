# PROBLEM STATEMENT:
# 7.9: Control Raspberry Pi Digital input with Python by interfacing DHT11
# sensor with respective GPIO ports and monitoring the Temperature and
# humidity parameters on screen


import RPi.GPIO as GPIO 
import time 
import urllib.request 
import Adafruit_DHT 

GPIO.setmode(GPIO.BCM) 
pin = 22 

while True: 
    humidity, temperature = Adafruit_DHT.read_retry(Adafruit_DHT.DHT11, pin) 
    if humidity is not None and temperature is not None: 
        print('Temp={0:0.1f}*  Humidity={1:0.1f}%'.format(temperature, humidity)) 
    else: 
        print('Failed to get reading. Try again!') 
    time.sleep(2)
