#define BLYNK_TEMPLATE_ID "Enter_Template_ID"
#define BLYNK_TEMPLATE_NAME "Enter_Project_Name"
#define BLYNK_AUTH_TOKEN "Enter_Your_Blynk_Token"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Enter_Your_SSID";
char pass[] = "Enter_Your_Password";

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
}

void loop() {
  Blynk.run();
}
