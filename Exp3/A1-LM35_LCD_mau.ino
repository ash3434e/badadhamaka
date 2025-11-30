#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);   
#define LM35PIN A0  

void setup() {
  Serial.begin(9600);
  lcd.init();             
  lcd.backlight();        
  lcd.clear();            
}
void loop() {
  int sensorValue = analogRead(LM35PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  float celsius = voltage * 100.0;
  float fahrenheit = (celsius * 9.0 / 5.0) + 32.0;  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TempC: ");
  lcd.print(celsius, 1);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("TempF: ");
  lcd.print(fahrenheit, 1);
  lcd.print(" F");
  delay(2000);
}
