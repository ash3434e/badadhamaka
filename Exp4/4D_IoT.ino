#define BLYNK_TEMPLATE_ID "Enter_Template_ID"
#define BLYNK_TEMPLATE_NAME "Enter_Project_Name"
#define BLYNK_AUTH_TOKEN "Enter_Blynk_Token"

#include <SoftwareSerial.h>
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

char ssid[] = "Enter_Your_SSID";
char pass[] = "Enter_Your_Password";
char auth[] = BLYNK_AUTH_TOKEN;

SoftwareSerial EspSerial(2, 3);
ESP8266 wifi(&EspSerial);

#define RELAY1 8
#define RELAY2 9
#define RELAY3 10
#define RELAY4 11

void setup() {
  Serial.begin(9600);
  delay(1000);

  EspSerial.begin(9600);
  delay(1000);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);
  digitalWrite(RELAY3, LOW);
  digitalWrite(RELAY4, LOW);

  Blynk.begin(auth, wifi, ssid, pass);
}

void loop() {
  Blynk.run();
}

BLYNK_WRITE(V1) { digitalWrite(RELAY1, param.asInt()); }
BLYNK_WRITE(V2) { digitalWrite(RELAY2, param.asInt()); }
BLYNK_WRITE(V3) { digitalWrite(RELAY3, param.asInt()); }
BLYNK_WRITE(V4) { digitalWrite(RELAY4, param.asInt()); }
