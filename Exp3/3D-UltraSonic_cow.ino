#define TRIG_PIN 9
#define ECHO_PIN 10

long duration;
float distanceCm;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.println("Distance measurement using HC-SR04");
  Serial.println("Observation Table:");
  Serial.println("Count\tDistance(Cm)");
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distanceCm = (duration * 0.0343) / 2;

  static int count = 1;

  Serial.print(count);
  Serial.print("\t");
  Serial.println(distanceCm);

  count++;

  delay(1000);
}
