//LM35


#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int lm35Pin = A0;

void setup() {
  lcd.init();              
  lcd.backlight();         
  Serial.begin(9600);
  
  Serial.println("Time(s)\tTemp (°C)\tTemp (°F)");
}

void loop() {
  static unsigned long startTime = millis();
  
  int sensorValue = analogRead(lm35Pin);
  
  float voltage = sensorValue * (5.0 / 1023.0);
  float tempC = voltage * 100.0;

  tempC -= 110;

  float tempF = (tempC * 9.0 / 5.0) + 32.0;
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TempC: ");
  lcd.print(tempC, 1);
  lcd.write(223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("TempF: ");
  lcd.print(tempF, 1);
  lcd.write(223);
  lcd.print("F");
  
  unsigned long elapsedSec = (millis() - startTime) / 1000;
  Serial.print(elapsedSec);
  Serial.print("\t");
  Serial.print(tempC, 1);
  Serial.print("\t\t");
  Serial.println(tempF, 1);
  

  Serial.print("Raw ADC: ");
  Serial.print(sensorValue);
  Serial.print("   Voltage: ");
  Serial.println(voltage, 3);
  
  delay(2000);
}
