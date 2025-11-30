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

#define MINPRESSURE 10
#define MAXPRESSURE 1000

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define BLACK   0x0000
#define WHITE   0xFFFF

const int NP = 12;

struct Particle {
  int x, y;
  int vx, vy;
  uint16_t color;
};

Particle part[NP];

int brushX = -1, brushY = -1;
int hue = 0;

uint16_t HSVtoRGB(int h);

void setup() {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.print("Touch/drag for\n CRAZY EFFECT!");

  int xc = tft.width() / 2, yc = tft.height() / 2;
  for (int i = 0; i < NP; i++) {
    part[i].x = xc;
    part[i].y = yc;
    float angle = 2.0 * PI * i / NP;
    part[i].vx = cos(angle) * (random(3, 5));
    part[i].vy = sin(angle) * (random(3, 5));
    part[i].color = HSVtoRGB((i * 360 / NP) % 360);
  }
}

void loop() {
  for (int i = 0; i < NP; i++) {
    tft.fillCircle(part[i].x, part[i].y, 4, part[i].color);
    part[i].x += part[i].vx;
    part[i].y += part[i].vy;

    if (part[i].x < 4 || part[i].x > tft.width() - 4)  part[i].vx = -part[i].vx;
    if (part[i].y < 4 || part[i].y > tft.height() - 4) part[i].vy = -part[i].vy;
  }

  TSPoint p = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    int tx = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    int ty = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    int xc = tx, yc = ty;
    for (int i = 0; i < NP; i++) {
      float angle = 2.0 * PI * i / NP + random(10) / 10.0;
      part[i].x = xc;
      part[i].y = yc;
      part[i].vx = cos(angle) * (random(4, 10));
      part[i].vy = sin(angle) * (random(4, 10));
      part[i].color = HSVtoRGB(random(360));
    }

    if (brushX != -1) {
      for (int d = 0; d < 8; d++)
        tft.drawLine(brushX, brushY, tx, ty, HSVtoRGB((hue + d * 10) % 360));
    }
    brushX = tx; 
    brushY = ty;
    hue = (hue + 14) % 360;
  } else {
    brushX = brushY = -1;
  }

  delay(20);
}

uint16_t HSVtoRGB(int h) {
  float s = 1.0, v = 1.0;
  float c = v * s;
  float x = c * (1 - abs((h / 60)%2 - 1));
  float m = v - c;
  float r, g, b;

  if(h < 60)      { r = c, g = x, b = 0; }
  else if(h < 120){ r = x, g = c, b = 0; }
  else if(h < 180){ r = 0, g = c, b = x; }
  else if(h < 240){ r = 0, g = x, b = c; }
  else if(h < 300){ r = x, g = 0, b = c; }
  else            { r = c, g = 0, b = x; }

  uint8_t R = (r + m)*31, G = (g + m)*63, B = (b + m)*31;
  return (R << 11) | (G << 5) | B;
}
