#include <DHT.h>
#define DHTPIN 2  
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin();
}
void loop() {
  delay(2000);
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(tempC);
  Serial.print(" °C  ,  ");
  Serial.print("Fahrenheit: ");
  Serial.print(tempF);
  Serial.println(" °F");
}
