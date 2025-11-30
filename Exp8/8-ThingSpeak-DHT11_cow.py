import RPi.GPIO as GPIO
import time
import Adafruit_DHT
import urllib.request

pin = 2
api_key = "ENTER_YOUR_API_KEY"

while True:
    humidity, temperature = Adafruit_DHT.read_retry(Adafruit_DHT.DHT11, pin)

    if humidity is not None and temperature is not None:
        print("Temp = {:.1f}°C  Humidity = {:.1f}%".format(temperature, humidity))
    else:
        print("Sensor error!")

    time.sleep(2)

    url = f"https://api.thingspeak.com/update?api_key={api_key}&field1={temperature}&field2={humidity}"
    response = urllib.request.urlopen(url)
    print(response.read())
    response.close()
