# PROBLEM STATEMENT:
# 7.8: Control Raspberry Pi Digital Outputs with Python by interfacing LEDs
# with respective GPIO ports. 


import RPi.GPIO as GPIO 
from time import sleep 

GPIO.setmode(GPIO.BCM) 

led_pins = [17, 22, 27] 

for pin in led_pins: 
    GPIO.setup(pin, GPIO.OUT) 

while True: 
    for pin in led_pins: 
        GPIO.output(pin, GPIO.HIGH) 
        sleep(1) 
    for pin in led_pins: 
        GPIO.output(pin, GPIO.LOW) 
        sleep(1) 
