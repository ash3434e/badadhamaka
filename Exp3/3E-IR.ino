/*Problem Statement E: To interface an Infrared (IR) sensor module with an Arduino to de-
tect and count the presence of objects. The count of detected objects
will be displayed on a 4-digit 7-segment display using I2C communica-
tion TM1637.*/


#include <TM1637Display.h>

#define IR_SENSOR_PIN 2
#define CLK 3
#define DIO 4

TM1637Display display(CLK, DIO);

volatile int objectCount = 0;
bool objectDetected = false;

void setup() {
  pinMode(IR_SENSOR_PIN, INPUT);
  display.setBrightness(0x0f); 
  display.showNumberDec(0);  

  attachInterrupt(digitalPinToInterrupt(IR_SENSOR_PIN), detectObject, FALLING);
}

void loop() {
  display.showNumberDec(objectCount);
  delay(100); 
}

void detectObject() {
  
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if (interruptTime - lastInterruptTime > 200) {
    objectCount++;
  }

  lastInterruptTime = interruptTime;
}
