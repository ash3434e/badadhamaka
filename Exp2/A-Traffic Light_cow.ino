#include <TM1637Display.h>

#define CLK 2
#define DIO 3
TM1637Display display(CLK, DIO);

const int redPins[4] =    {4, 7, 10, 13};
const int yellowPins[4] = {5, 8, 11, A0};
const int greenPins[4] =  {6, 9, 12, A1};

const int GREEN_TIME = 10;
const int YELLOW_TIME = 2;

unsigned long phaseStartTime = 0;
unsigned long currentMillis = 0;
int phaseTime = 0;
int dir = 0;
int phase = 0;
bool initPhase = true;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(redPins[i], OUTPUT);
    pinMode(yellowPins[i], OUTPUT);
    pinMode(greenPins[i], OUTPUT);
  }
  display.setBrightness(0x0f);
}

void loop() {
  currentMillis = millis();

  if (initPhase) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(redPins[i], HIGH);
      digitalWrite(yellowPins[i], LOW);
      digitalWrite(greenPins[i], LOW);
    }

    if (phase == 0) {
      digitalWrite(redPins[dir], LOW);
      digitalWrite(greenPins[dir], HIGH);
      phaseTime = GREEN_TIME;
    } else {
      digitalWrite(redPins[dir], LOW);
      digitalWrite(greenPins[dir], LOW);
      digitalWrite(yellowPins[dir], HIGH);
      phaseTime = YELLOW_TIME;
    }

    phaseStartTime = currentMillis;
    initPhase = false;
  }

  int timeLeft = phaseTime - ((currentMillis - phaseStartTime) / 1000);
  if (timeLeft < 0) timeLeft = 0;
  display.showNumberDecEx(timeLeft, 0b01000000, true);

  if (currentMillis - phaseStartTime >= (phaseTime * 1000UL)) {
    if (phase == 0) {
      phase = 1;
    } else {
      phase = 0;
      dir = (dir + 1) % 4;
    }
    initPhase = true;
  }
}
