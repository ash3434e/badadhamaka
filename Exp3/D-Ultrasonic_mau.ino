#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#define TRIG 3
#define ECHO 4

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long echoTime = pulseIn(ECHO, HIGH);
  float dist = echoTime * 0.034 / 2;     

  Serial.print("Distance observed: ");
  Serial.print(dist, 1);
  Serial.println(" cm");
  delay(2000);
}
