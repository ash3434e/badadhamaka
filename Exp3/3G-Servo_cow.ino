#include <Servo.h>

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(9);
}

void loop() {
  for (int pos = 0; pos <= 180; pos++) {
    myServo.write(pos);
    Serial.print("Servo Position: ");
    Serial.println(pos);
    delay(15);
  }

  delay(500);

  for (int pos = 180; pos >= 0; pos--) {
    myServo.write(pos);
    Serial.print("Servo Position: ");
    Serial.println(pos);
    delay(15);
  }

  delay(500);
}
