#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x3F
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);

void setup() {
  Wire.begin();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Your Name");
  lcd.setCursor(0, 1);
  lcd.print("Enter Your GR No.");
}

void loop() {
}
