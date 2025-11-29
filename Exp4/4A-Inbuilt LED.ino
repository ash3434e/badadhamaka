/*A-PROBLEM STATEMENT
Interfacing of Inbuilt LED (connected to GPIO1 for ESP-01 or GPIO2
for ESP-01S) to ESP01/ESP01S/ESP8266 module and program in Em-
bedded C to blink a LED for every 1 second delay*/


void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(1000);                      
  digitalWrite(LED_BUILTIN, LOW);   
  delay(1000);                     
}
