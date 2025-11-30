#define BLYNK_TEMPLATE_ID "--"
#define BLYNK_TEMPLATE_NAME "--"
#define BLYNK_AUTH_TOKEN "--"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "--";
char pass[] = "--";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
}

void loop()
{
  Blynk.run();
}
