/*F-PROBLEM STATEMENT
Interface a Passive Infrared (PIR) sensor module with an Arduino
to detect motion. When motion is detected, an LED connected to the
Arduino should light up.*/


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


int pirPin = 2;      
int ledPin = 13;   

void setup() {
  pinMode(pirPin, INPUT);   
  pinMode(ledPin, OUTPUT);  
  Serial.begin(9600);    
}

void loop() {
  int motionDetected = digitalRead(pirPin); 

  if (motionDetected == HIGH) {
    digitalWrite(ledPin, HIGH);   
    Serial.println("Motion detected!");
  } else {
    digitalWrite(ledPin, LOW);    
    Serial.println("No motion");
  }

  delay(200);
