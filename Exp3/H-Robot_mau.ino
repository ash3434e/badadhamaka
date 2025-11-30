const int ENA = 9;   
const int IN1 = 8;
const int IN2 = 7;


const int ENB = 3;   
const int IN3 = 5;
const int IN4 = 4;


const int TRIG_PIN = 11;
const int ECHO_PIN = 10;

int motorSpeed = 200;      
const int obstacleDist = 20; 


void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);


  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);


  Serial.begin(9600);
  stopMotors();
}


void loop() {
  long d = getDistanceCM();
  Serial.print("Distance: "); Serial.println(d);

  if (d > 0 && d <= obstacleDist) {
    
    driveBackward(motorSpeed);
    delay(500);
    stopMotors();
    delay(200);
  } else {
   
    driveForward(motorSpeed);
  }
  delay(50);
}


void driveForward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);


  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
}


void driveBackward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);


  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speed);
}


void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


long getDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);


  long duration = pulseIn(ECHO_PIN, HIGH, 30000UL); 
  if (duration == 0) return -1; 
  return duration / 58; 
}
