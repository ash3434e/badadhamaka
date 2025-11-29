#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <avr/pgmspace.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const unsigned char smiley_bmp[] PROGMEM = {
  0b00111100, 0b00000000,
  0b01000010, 0b00000000,
  0b10100101, 0b00000000,
  0b10000001, 0b00000000,
  0b10100101, 0b00000000,
  0b10011001, 0b00000000,
  0b01000010, 0b00000000,
  0b00111100, 0b00000000
};

int currentRotation = 2;

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  currentRotation = (currentRotation == 0) ? 2 : 0;
  display.setRotation(currentRotation);
  display.clearDisplay();

  // 1. Simple Text & Inverted Text
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.setTextColor(SSD1306_WHITE);
  display.println("Normal Text");

  display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);  
  display.println("Colour Inverted Text");

  display.setTextColor(SSD1306_WHITE); 

  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Big Txt");

  display.setTextSize(1);
  int num = 123;
  display.setCursor(0, 20);
  display.print("Dec: ");
  display.println(num);
  display.print("Hex: ");
  display.println(num, HEX);

  display.display();
  delay(2000);

  display.startscrollleft(0x00, 0x0F);
  delay(2000);
  display.stopscroll();

  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.stopscroll();

  display.clearDisplay();
  int scale = 4;
  int imgWidth = 16;
  int imgHeight = 8;

  for (int y = 0; y < imgHeight; y++) {
    for (int x = 0; x < imgWidth; x++) {
      byte row = pgm_read_byte(&smiley_bmp[y * 2 + (x / 8)]);
      if (row & (1 << (7 - (x % 8)))) {
        display.fillRect(30 + x * scale, 10 + y * scale, scale, scale, SSD1306_WHITE);
      }
    }
  }

  display.display();
  delay(2000);

  display.clearDisplay();
  display.drawRect(10, 10, 50, 30, SSD1306_WHITE);
  display.drawCircle(90, 32, 15, SSD1306_WHITE);
  display.drawTriangle(20, 55, 30, 40, 40, 55, SSD1306_WHITE);
  display.display();
  delay(2000);
}
