#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.blink();
}

void loop() {
  String name = "Rajlakshmi Desai";
  String prn = "22311732";

  lcd.setCursor(0, 0); 
  for (int i = 0; i < name.length(); i++) {
    lcd.print(name[i]);                            
    delay(200);
  }

  lcd.setCursor(0, 1); 
  for (int i = 0; i < prn.length(); i++) {
    lcd.print(prn[i]);
    delay(200);
  }
  delay(1000);  
  for (int i = 0; i < 3; i++) {
    lcd.scrollDisplayRight(); 
    delay(300);
  }
  delay(3000);
  lcd.clear();
  }
