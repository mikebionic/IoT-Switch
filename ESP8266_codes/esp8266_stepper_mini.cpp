#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
//Static IP address configuration
IPAddress staticIP(192, 168, 1, 213); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "azat";
const char* password = "oguzhan85";

int Step = 0; //GPIO0---D3 of Nodemcu--Step of stepper motor driver
int Dir  = 2; //GPIO2---D4 of Nodemcu--Direction of stepper motor driver

ESP8266WebServer server(80);

void stepForward() {
  digitalWrite(Dir, HIGH); //Rotate stepper motor in clock wise direction
  for(int i=1;i<=50;i++){
    digitalWrite(Step, HIGH);
    delay(100);
    digitalWrite(Step, LOW);
    delay(100);
  }
  server.send(200, "text/html", "Forward");
}
 
void stepBackward() {
  digitalWrite(Dir, LOW); //Rotate stepper motor in clock wise direction
  for(int i=1;i<=50;i++){
    digitalWrite(Step, HIGH);
    delay(100);
    digitalWrite(Step, LOW);
    delay(100);
  }
 server.send(200, "text/html", "Backward");
}

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(Step, OUTPUT); //Step pin as output
  pinMode(Dir,  OUTPUT); //Direcction pin as output
  digitalWrite(Step, LOW); // Currently no stepper motor movement
  digitalWrite(Dir, LOW);  

  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);

  WiFi.mode(WIFI_STA);
  
  delay(500);
  Serial.println("");
  Serial.println("WiFi connected");
 
  Serial.print(WiFi.localIP());

  server.on("/control/1", stepForward);
  server.on("/control/0", stepBackward);
  server.begin();
}
 
void loop() {
  server.handleClient();
}
