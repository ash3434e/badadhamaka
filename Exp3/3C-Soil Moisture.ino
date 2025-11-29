/*C-PROBLEM STATEMENT
Interface a soil moisture sensor YL-69 or HL-69 using analog output
with an Arduino, read the moisture level, and control a water motor
based on the soil moisture level. Write a program in Embedded C to
detect and display these values.
*/

#define MOISTURE_SENSOR_PIN A0    
#define SENSOR_DIGITAL_PIN 3       
#define RELAY_PIN 2                
#define BUZZER_PIN 9
#define LED_PIN 8

void setup() {
  pinMode(MOISTURE_SENSOR_PIN, INPUT);
  pinMode(SENSOR_DIGITAL_PIN, INPUT); 
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW); 
  Serial.begin(9600);
}

void loop() {
  int rawValue = analogRead(MOISTURE_SENSOR_PIN);
  int moisture = map(rawValue, 1023, 0, 0, 100); 
  moisture = constrain(moisture, 0, 100);

  Serial.print("Moisture: ");
  Serial.print(moisture);
  Serial.println("%");

  if (moisture < 10) {
    digitalWrite(RELAY_PIN, HIGH);  
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.println("Status: Dry - Pump ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);   
    digitalWrite(LED_PIN, LOW);
    Serial.println("Status: Wet - Pump OFF");
  }

  delay(1000);
}
