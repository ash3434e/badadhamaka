# PROBLEM STATEMENT:
# 8.8: Write a program in Python and Create a channel using Thing-speak
# IoT cloud to monitor/analyze the temperature and humidity data from
# DHT11 sensor with interfaced with Raspberry Pi


import RPi.GPIO as GPIO
import time
import Adafruit_DHT
import urllib.request

pin = 2
while True:
    humidity, temperature = Adafruit_DHT.read_retry(Adafruit_DHT.DHT11, pin)
    if humidity is not None and temperature is not None:
        print('Temp={0:0.1f}*C Humidity={1:0.1f}%'.format(temperature, humidity))
    else:
        print('Failed to get reading. Try again!')
    time.sleep(2)
    f = urllib.request.urlopen('https://api.thingspeak.com/update?api_key=&field1=%s&field2=%s'%(temperature, humidity))
    print(f.read())
    f.close()
