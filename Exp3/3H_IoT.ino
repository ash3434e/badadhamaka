int enA = 9;
int in1 = 8;
int in2 = 7;
int enB = 3;
int in3 = 5;
int in4 = 4;

const int ultrigPin = 10;
const int ultraEchoPin = 11;

const int irPin = 12;

const int obstacleDistance = 5;
const int irThreshold = LOW;

const int motorSpeed = 90;
const int backwardSpeed = 90;
const int turnSpeed = 90;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(ultrigPin, OUTPUT);
  pinMode(ultraEchoPin, INPUT);

  pinMode(irPin, INPUT);

  stopMotors();

  Serial.begin(9600);
}

void loop() {
  long distance = getDistance();
  int irValue = digitalRead(irPin);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, IR: ");
  Serial.println(irValue);

  if (distance <= obstacleDistance || irValue != irThreshold) {
    moveBackward();
    delay(1000);

    turn();
    delay(700);

    moveForward();
  } else {
    moveForward();
  }

  delay(100);
}

void moveForward() {
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void moveBackward() {
  analogWrite(enA, backwardSpeed);
  analogWrite(enB, backwardSpeed);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turn() {
  analogWrite(enA, turnSpeed);
  analogWrite(enB, turnSpeed);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  analogWrite(enA, 0);
  analogWrite(enB, 0);
}

long getDistance() {
  digitalWrite(ultrigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(ultrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrigPin, LOW);

  long duration = pulseIn(ultraEchoPin, HIGH, 30000);

  long distanceCm = duration * 0.034 / 2;

  if (duration == 0) {
    return 999;
  }
 
  return distanceCm;
}
