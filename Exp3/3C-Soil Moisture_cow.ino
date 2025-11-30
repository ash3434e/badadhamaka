#define MOISTURE_PIN A0
#define RELAY_PIN 2

int threshold = 900;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
}

void loop() {
  int moistureValue = analogRead(MOISTURE_PIN);

  Serial.print("Soil moisture reading: ");
  Serial.println(moistureValue);

  if (moistureValue > threshold) {
    Serial.println("Soil is DRY. Pump ON.");
    digitalWrite(RELAY_PIN, LOW);
  } else {
    Serial.println("Soil is WET. Pump OFF.");
    digitalWrite(RELAY_PIN, HIGH);
  }

  delay(2000);
}
