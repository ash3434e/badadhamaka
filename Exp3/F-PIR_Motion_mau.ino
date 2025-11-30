const int pir = 2;  
const int led = 3;    
int motionState = 0;      

void setup() {
  Serial.begin(9600);          
  pinMode(pir, INPUT_PULLUP);
  pinMode(led, OUTPUT);    
}

void loop() {
  if (digitalRead(pir) == HIGH) {
    digitalWrite(led, HIGH);
    Serial.println("Motion detected");
    delay(200);
  }
  else {
    Serial.println("No Motion");
    digitalWrite(led, LOW);
    delay(200);
  }
}
