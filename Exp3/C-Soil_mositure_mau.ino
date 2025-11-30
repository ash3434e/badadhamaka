#define Moisture_sensor A0     
#define Relay 9

void setup() {
  pinMode(Moisture_sensor, INPUT);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, LOW);
  Serial.begin(9600);
}

void loop() {
  int rawValue = analogRead(Moisture_sensor);
  int moisture = map(rawValue, 1023, 0, 0, 100);
  moisture = constrain(moisture, 0, 100);


  Serial.print("current moisture: ");
  Serial.print(moisture);
  Serial.println("%");
  if (moisture < 10) {
    digitalWrite(relay, HIGH);  
    Serial.println("sensor status-dry , pump ON");
  } else {
    digitalWrite(relay, LOW);   
    Serial.println("sensor status-wet , pump OFF");
  }
  delay(1000);
}
