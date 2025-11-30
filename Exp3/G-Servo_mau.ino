#include <Servo.h>
Servo s1;

void setup() {
  Serial.begin(9600);      
  s1.attach(9);      
}
void loop() {

  for (int degree = 0; degree <= 180; degree++) {
    s1.write(degree);  
    Serial.print("angle: ");
    Serial.println(degree);
    delay(45);            
  }
  
  for (int degree = 180; degree >= 0; degree--) {
    s1.write(degree);
    Serial.print("angle: ");
    Serial.println(degree);
    delay(45);
  }
}
