/*A-PROBLEM STATEMENT-2
To interface an LM35 temperature sensor with an Arduino Uno
Nano, read temperature values, display these values in both Celsius and
Fahrenheit on an OLED screen, and record the readings
in an observation table over a period of time.
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int lm35Pin = A0;

void setup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.display();

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

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temperature:");

  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(tempC, 2);
  display.cp437(true);
  display.write(248);
  display.print("C");

  display.setTextSize(1);
  display.setCursor(0, 35);
  display.print("Temperature:");

  display.setTextSize(2);
  display.setCursor(0, 45);
  display.print(tempF, 2);
  display.cp437(true);
  display.write(248);
  display.print("F");

  display.display();

  unsigned long elapsedSec = (millis() - startTime) / 1000;
  Serial.print(elapsedSec);
  Serial.print("\t");
  Serial.print(tempC, 2);
  Serial.print("\t\t");
  Serial.println(tempF, 2);

  delay(2000);
}
