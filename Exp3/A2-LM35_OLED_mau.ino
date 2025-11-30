#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define LM35PIN A0  


void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1.9);
  display.setTextColor(SSD1306_WHITE);
}


void loop() {
  int sensorValue = analogRead(LM35PIN);
  float voltage = sensorValue * (5.0 / 1023.0);
  float celsius = voltage * 100.0;
  float fahrenheit = (celsius * 9.0 / 5.0) + 32.0;
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(celsius);
  display.println(" C");
  display.print("Temp: ");
  display.print(fahrenheit);
  display.println(" F");
  display.display();
  delay(2000);}
