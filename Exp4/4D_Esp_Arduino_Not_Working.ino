/*D-PROBLEM STATEMENT: Interface WiFi ESP01/ESP8266 module with Arduino UNO/NANO and con-
trol four LEDs/Relays connected to Arduino board through WiFi module Access
Point (AP) without a router using BLYNK Cloud platform.
*/

#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""


#include <SoftwareSerial.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char ssid[] = "";
char pass[] = "";

char auth[] = BLYNK_AUTH_TOKEN;


SoftwareSerial EspSerial(2, 3); 
ESP8266 wifi(&EspSerial);

#define RELAY1 8
#define RELAY2 9
#define RELAY3 10
#define RELAY4 11

void setup()
{

  Serial.begin(9600);
  delay(1000);
  Serial.println("=== Arduino UNO + ESP8266 Relay Control ===");

  EspSerial.begin(9600);
  delay(1000);
  Serial.println("ESP8266 Serial started at 9600");

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
  digitalWrite(RELAY4, LOW);

  Serial.println("Connecting to Blynk...");
  Blynk.begin(auth, wifi, ssid, pass);
  Serial.println("System Ready!");
}

void loop()
{
  Blynk.run();
}

BLYNK_WRITE(V1) { digitalWrite(RELAY1, param.asInt()); }
BLYNK_WRITE(V2) { digitalWrite(RELAY2, param.asInt()); }
BLYNK_WRITE(V3) { digitalWrite(RELAY3, param.asInt()); }
BLYNK_WRITE(V4) { digitalWrite(RELAY4, param.asInt()); }
