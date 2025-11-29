/*B-PROBLEM STATEMENT
Interfacing DHT11/DHT22 Humidity and Temperature Sensor With
Arduino Write a program in Embedded C to detect temperature and hu-
midity and print the values to the Serial Monitor.
*/

#include "DHT.h"

#define DHTPIN 2       
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);       
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();             
  float temperatureC = dht.readTemperature();      
  float temperatureF = dht.readTemperature(true); 


  if (isnan(humidity) || isnan(temperatureC) || isnan(temperatureF)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print(" *C  ");
  
  Serial.print(temperatureF);
  Serial.println(" *F");

  delay(2000);
}