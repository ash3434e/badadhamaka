/*Problem Statement D: Interface an ultrasonic sensor HC-SR04 with an Arduino to measure
the distance to an object and display the measured distance on the
serial monitor. Additionally, log the actual and observed data in an
observation table.*/

#define TRIG_PIN 9
#define ECHO_PIN 10

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(15);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 60000);

  if (duration == 0) {
    Serial.println("Out of range or no echo");
  } else {
    float distance_cm = duration * 0.0343 / 2;
    Serial.print("Distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
  }

  delay(1000);
}
