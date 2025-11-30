#include <Adafruit_GFX.h>      
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>       

#define LCD_CS   A3  
#define LCD_CD   A2  
#define LCD_WR   A1  
#define LCD_RD   A0  
#define LCD_RESET A4  
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
#define YP A1  
#define XM A2  
#define YM 7  
#define XP 6  
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); 

uint16_t colors[] = {0xF800, 0x07E0, 0x001F}; 
byte colorIndex = 0; 


void setup() {
  tft.begin(0x9341);          
  tft.setRotation(1);         
  tft.fillScreen(colors[0]);  
}
void loop() {
  
  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > 50 && p.z < 1000) {
    colorIndex = (colorIndex + 1) % 3;     
    tft.fillScreen(colors[colorIndex]);     
    delay(300);                            
  }}
