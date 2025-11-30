#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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


void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}


void loop() {
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Rajlakshmi Desai");
  display.display();
  delay(2000);
  
  display.startscrollright(0x00, 0x0F);  
  delay(2000);
  display.stopscroll();  
  display.clearDisplay();
 
  display.drawRect(10, 10, 30, 30, SSD1306_WHITE);
  display.drawCircle(70, 25, 15, SSD1306_WHITE);
  display.drawTriangle(100, 10, 120, 40, 80, 40, SSD1306_WHITE);
  display.display();
  delay(2000);
  display.clearDisplay();
 
  int number = 123;
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("Decimal: ");
  display.println(number);
  display.print("Hex: ");
  display.println(number, HEX);
  display.display();
  delay(3000);
  display.clearDisplay();

  display.setTextSize(3);
  display.setCursor(0, 0);
  display.print("Big");
  display.display();
  delay(2000);
  display.clearDisplay();
 
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

  display.clearDisplay();
  display.ssd1306_command(SSD1306_SEGREMAP);  
  display.ssd1306_command(SSD1306_COMSCANINC);  
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("Inverted ");
  display.display();
  delay(2000);
}
