#include <TM1637Display.h>

#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

const int irSensorPin = 7;

int count = 0;
bool objectDetected = false;

void setup() {
  pinMode(irSensorPin, INPUT);
  display.setBrightness(0x0f);
  display.showNumberDec(0);
  Serial.begin(9600);
}

void loop() {
  int sensorState = digitalRead(irSensorPin);

  if (sensorState == LOW) {
    if (!objectDetected) {
      count++;
      display.showNumberDec(count);
      Serial.print("Object count: ");
      Serial.println(count);
      objectDetected = true;
    }
  } else {
    objectDetected = false;
  }

  delay(100);
}
