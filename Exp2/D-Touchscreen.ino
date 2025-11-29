#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>

MCUFRIEND_kbv tft;


#define YP A1 
#define XM A2  
#define YM 7   
#define XP 6

#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define BLUE    0x001F
#define WHITE   0xFFFF
#define YELLOW  0xFFE0

int ballX = 100, ballY = 100;
int ballDX = 3, ballDY = 2;
int ballRadius = 10;

void setup() {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(30, 10);
  tft.print("Touch to change color");
}

void loop() {
  tft.fillCircle(ballX, ballY, ballRadius, BLACK);

  ballX += ballDX;
  ballY += ballDY;


  if (ballX < ballRadius || ballX > tft.width() - ballRadius) ballDX = -ballDX;
  if (ballY < ballRadius || ballY > tft.height() - ballRadius) ballDY = -ballDY;

  tft.fillCircle(ballX, ballY, ballRadius, RED);

  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    int tx = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    int ty = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    tft.fillScreen(randomColor());
    tft.setCursor(30, 10);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Color Changed!");
    delay(500); 
  }

  delay(20);
}

uint16_t randomColor() {
  switch (random(5)) {
    case 0: return RED;
    case 1: return GREEN;
    case 2: return BLUE;
    case 3: return YELLOW;
    default: return WHITE;
  }
}