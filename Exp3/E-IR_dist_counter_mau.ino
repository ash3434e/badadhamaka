#include <TM1637Display.h>
#define clk 2  
#define dio 3  
#define IR 4
#define Reset 5

TM1637Display segDisplay(clk, dio);

int objCount = 0;
bool objPresent = false;

void setup() {
  pinMode(IR, INPUT);
  pinMode(Reset, INPUT_PULLUP);
  segDisplay.setBrightness(0x0f);
  Serial.begin(9600);
}

void loop() {
  if (!digitalRead(Reset)) { 
    objCount = 0;
  }
  else if (!digitalRead(IR) && !objPresent) {
    objCount++;
    objPresent = true;
  }
  else if (digitalRead(IR)) {
    objPresent = false;
  }
  segDisplay.showNumberDec(objCount);
  delay(100);
}
