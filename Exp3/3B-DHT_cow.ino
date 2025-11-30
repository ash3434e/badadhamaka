#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT Sensor Temperature and Humidity Test");
  dht.begin();
}

void loop() {
  delay(2000);

  unsigned long seconds = millis() / 1000;
  unsigned int hours = seconds / 3600;
  unsigned int minutes = (seconds % 3600) / 60;
  unsigned int sec = seconds % 60;

  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);

  if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Time: ");
  if (hours < 10) Serial.print('0');
  Serial.print(hours); Serial.print(":");
  if (minutes < 10) Serial.print('0');
  Serial.print(minutes); Serial.print(":");
  if (sec < 10) Serial.print('0');
  Serial.print(sec); Serial.print("  ");

  Serial.print("Humidity: ");
  Serial.print(humidity); Serial.print("%  ");

  Serial.print("Temp: ");
  Serial.print(tempC); Serial.print("°C  ");
  Serial.print(tempF); Serial.println("°F");
}
