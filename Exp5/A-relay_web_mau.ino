#include <ESP8266WiFi.h>

const char* ssid  = "--";    
const char* password = "--";   

WiFiServer server(80);

String header;
String relay1State = "off";
String relay2State = "off";

const int relay1Pin = 12; 
const int relay2Pin = 4;  

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);

  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);

  digitalWrite(relay1Pin, HIGH);
  digitalWrite(relay2Pin, HIGH);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    currentTime = millis();
    previousTime = currentTime;

    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      currentTime = millis();
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
           
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /relay1/on") >= 0) {
              Serial.println("Relay 1 ON");
              relay1State = "on";
              digitalWrite(relay1Pin, LOW);   
            } else if (header.indexOf("GET /relay1/off") >= 0) {
              Serial.println("Relay 1 OFF");
              relay1State = "off";
              digitalWrite(relay1Pin, HIGH);  
            } else if (header.indexOf("GET /relay2/on") >= 0) {
              Serial.println("Relay 2 ON");
              relay2State = "on";
              digitalWrite(relay2Pin, LOW); 
            } else if (header.indexOf("GET /relay2/off") >= 0) {
              Serial.println("Relay 2 OFF");
              relay2State = "off";
              digitalWrite(relay2Pin, HIGH);  
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<head><title>ESP8266 Web Control</title>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>");
            client.println("body { font-family: Arial, sans-serif; text-align: center; padding: 20px; }");
            client.println(".info { font-size: 18px; margin: 8px 0; }");
            client.println(".switch { position: relative; display: inline-block; width: 60px; height: 34px; margin: 10px;}");
            client.println(".switch input {opacity: 0; width: 0; height: 0;}");
            client.println(".slider {position: absolute;cursor: pointer;top: 0; left: 0; right: 0; bottom: 0;");
            client.println("background-color: #ccc;transition: .4s;border-radius: 34px;}");
            client.println(".slider:before {position: absolute;content: \"\";height: 26px;width: 26px;left: 4px;bottom: 4px;");
            client.println("background-color: white;transition: .4s;border-radius: 50%;}");
            client.println("input:checked + .slider {background-color: #4CAF50;}");
            client.println("input:checked + .slider:before {transform: translateX(26px);}");
            client.println("</style></head><body>");
            client.println("<h2>IoT Practical</h2>");
            client.println("<p class=\"info\"><b>Name:</b>------------------</p>");
            client.println("<p class=\"info\"><b>Roll No:</b>----------</p>");
            client.println("<p class=\"info\"><b>Experiment 5:</b>---------------</p>");

            client.println("<div><p><b>Relay 1 (D6)</b></p>");
            client.print("<label class=\"switch\"><input type=\"checkbox\" ");
            if (relay1State == "on") client.print("checked ");
            client.println("onclick=\"toggleSwitch(1,this)\"><span class=\"slider\"></span></label></div>");

            client.println("<div><p><b>Relay 2 (D2)</b></p>");
            client.print("<label class=\"switch\"><input type=\"checkbox\" ");
            if (relay2State == "on") client.print("checked ");
            client.println("onclick=\"toggleSwitch(2,this)\"><span class=\"slider\"></span></label></div>");

            client.println("<script>");
            client.println("function toggleSwitch(num,el){");
            client.println("if(num==1){if(el.checked){window.location.href='/relay1/on';}else{window.location.href='/relay1/off';}}");
            client.println("if(num==2){if(el.checked){window.location.href='/relay2/on';}else{window.location.href='/relay2/off';}}");
            client.println("}");
            client.println("</script>");


            client.println("</body></html>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
