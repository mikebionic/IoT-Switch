#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define pin1 0
#define pin2 1
#define button1pin 2
#define button2pin 3

long operateTime = millis();
int oneRevolutionTime = 15000;

IPAddress staticIP(192, 168, 1, 210); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway) 
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "ssid";
const char* password = "password";
const char* deviceName = "Smart curtain v2";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "curtain_hash";

ESP8266WebServer server(80);


void handleUp() {
  if (digitalRead(button1pin) != 1){
    long currentTime = millis();

    while (operateTime - oneRevolutionTime < currentTime){
      digitalWrite(pin1, 0);
      digitalWrite(pin2, 1);
      operateTime = millis();
      if (digitalRead(button1pin) == 1){
        break;
      }
    }

    server.send(200, "text/html", "up");
  }

  else {
    server.send(200, "text/html", "up error (treshold)");
  }

  digitalWrite(pin1, 0);
  digitalWrite(pin2, 0);
}


void handleDown() {
  if (digitalRead(button2pin) != 1){
    long currentTime = millis();

    while (operateTime - oneRevolutionTime < currentTime){
      digitalWrite(pin1, 1);
      digitalWrite(pin2, 0);
      operateTime = millis();
      if (digitalRead(button2pin) == 1){
        break;
      }
    }

    server.send(200, "text/html", "down");
  }

  else {
    server.send(200, "text/html", "down error (treshold)");
  }

  digitalWrite(pin1, 0);
  digitalWrite(pin2, 0);
}


void setup(void){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  pinMode(pin1, OUTPUT); 
  pinMode(pin2, OUTPUT);
  pinMode(button1pin, INPUT);
  pinMode(button2pin, INPUT);
  digitalWrite(pin1, 0);
  digitalWrite(pin2, 0);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/up", handleUp);
  server.on("/down", handleDown);
  server.begin();
  Serial.println("HTTP server started");
}


void loop(void){
  server.handleClient(); 
}