/*C-PROBLEM STATEMENT
Initialisation of ESP01 wifi module and controlling the Relay/LED connected
to GPIO0 port pin of ESP0 module using BLYNK Cloud Platform or any ESP8266
configuration app using access point (AP) mode.
*/

#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "";
char pass[] = "";

void setup()
{
  Serial.begin(115200);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
}

void loop()
{
  Blynk.run();
}
