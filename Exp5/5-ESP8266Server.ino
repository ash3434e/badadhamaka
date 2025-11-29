/* PROBLEM STATEMENT:
Build a NodeMCU ESP8266 based web-server and demonstrate the
application to control the LEDs or relay connected to respective GPIO
ports of ESP8266 NodeMCU.
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "";
const char* password = "";


IPAddress local_ip(192,168,4,1);
IPAddress gateway(192,168,4,1);
IPAddress subnet(255,255,255,0);


ESP8266WebServer server(80);

const uint8_t RELAY1 = D6; // IN1 of Relay module
const uint8_t RELAY2 = D7; // IN2 of Relay module

bool relayState = LOW; 


void setup() {
  Serial.begin(115200);

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

  digitalWrite(RELAY1, relayState ? LOW : HIGH);
  digitalWrite(RELAY2, relayState ? LOW : HIGH);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.on("/", handle_OnConnect);
  server.on("/toggle", handle_ToggleRelay);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Server started at http://192.168.4.1/");
}

void loop() {
  server.handleClient();

  digitalWrite(RELAY1, relayState ? LOW : HIGH);
  digitalWrite(RELAY2, relayState ? LOW : HIGH);
}

void handle_OnConnect() {
  Serial.println("Client connected");
  server.send(200, "text/html", SendHTML(relayState));
}

void handle_ToggleRelay() {
  relayState = !relayState;

  digitalWrite(RELAY1, relayState ? LOW : HIGH);
  digitalWrite(RELAY2, relayState ? LOW : HIGH);

  Serial.println(relayState ? "Relays ON" : "Relays OFF");
  server.send(200, "text/html", SendHTML(relayState));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not Found");
}

String SendHTML(bool state) {
  String statusText  = state ? "Relays are ON" : "Relays are OFF";
  String statusColor = state ? "#28a745" : "#dc3545";
  String checked     = state ? "checked" : "";

  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ESP8266 Relay Control</title>
<style>
* { margin: 0; padding: 0; box-sizing: border-box; }
body {
  font-family: 'Segoe UI', Tahoma, sans-serif;
  background: linear-gradient(135deg, #dff9fb, #c7ecee);
  display: flex; justify-content: center; align-items: center;
  min-height: 100vh;
}
.container {
  background: #fff; padding: 40px 50px; border-radius: 25px;
  box-shadow: 0 12px 30px rgba(0,0,0,0.2);
  text-align: center; width: 450px;
}
h1 { color: #003366; margin-bottom: 20px; font-size: 26px; }
h3 { color: #444; margin: 6px 0; font-size: 18px; }
.status {
  margin: 25px 0; font-size: 20px; font-weight: bold; color:
)rawliteral";

  html += statusColor;

  html += R"rawliteral(;
}
.switch {
  position: relative; display: inline-block;
  width: 80px; height: 40px;
}
.switch input { opacity: 0; width: 0; height: 0; }
.slider {
  position: absolute; cursor: pointer; top: 0; left: 0; right: 0; bottom: 0;
  background-color: #ccc; transition: .4s; border-radius: 40px;
}
.slider:before {
  position: absolute; content: ""; height: 30px; width: 30px;
  left: 5px; bottom: 5px;
  background-color: white; transition: .4s; border-radius: 50%;
}
input:checked + .slider { background-color: #28a745; }
input:checked + .slider:before { transform: translateX(40px); }
.switch-label {
  margin-top: 10px; font-size: 18px; font-weight: bold; color: #333;
}
</style>
</head>
<body>
<div class="container">
<h1>Exp 5: ESP8266 Relay Control</h1>
<h3>Name: <b>Name: </b></h3>
<h3>Roll No: <b>Roll Numnber: </b></h3>
<h3>PRN: <b>PRN: </b></h3>
<div class="status">)rawliteral";

  html += statusText;

  html += R"rawliteral(</div>
<label class="switch">
<input type="checkbox" onclick="location.href='/toggle'" )rawliteral";

  html += checked;

  html += R"rawliteral(>
<span class="slider"></span>
</label>
<div class="switch-label">Toggle Both Relays</div>
</div>
</body>
</html>
)rawliteral";

  return html;
}
