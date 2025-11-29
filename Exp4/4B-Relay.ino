/*B-PROBLEM STATEMENT
Interfacing of Relay module to ESP01 and controlling the applica-
tions connected to Relay through GPIO0 port pin
*/

#define RELAY_PIN 0  

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); 
}

void loop() {
 
  digitalWrite(RELAY_PIN, LOW);   
  delay(5000);
  digitalWrite(RELAY_PIN, HIGH);
  delay(5000); 
}