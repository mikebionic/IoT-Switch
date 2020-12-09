 #include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
//Static IP address configuration
IPAddress staticIP(192, 168, 1, 214); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "ssid";
const char* password = "password";

int Step = 3; //GPIO0---D3 of Nodemcu--Step of stepper motor driver
int Dir  = 1; //GPIO2---D4 of Nodemcu--Direction of stepper motor driver
int sw = 0;

ESP8266WebServer server(80);

const int stepsPerRevolution = 200;

void stepForward() {
  digitalWrite(sw, HIGH);
  digitalWrite(Dir, HIGH); //Rotate stepper motor in clock wise direction
  for(int x = 0; x < stepsPerRevolution; x++){
    digitalWrite(Step, HIGH);
    delay(5);
    digitalWrite(Step, LOW);
    delay(5);
  }
  digitalWrite(sw, LOW);
  server.send(200, "text/html", "Forward");
}
 
void stepBackward() {
  digitalWrite(sw, HIGH);
  digitalWrite(Dir, LOW); //Rotate stepper motor in clock wise direction
  for(int x = 0; x < stepsPerRevolution; x++){
    digitalWrite(Step, HIGH);
    delay(5);
    digitalWrite(Step, LOW);
    delay(5);
  }
  digitalWrite(sw, LOW);
  server.send(200, "text/html", "Backward");
}
void ocur(){
  digitalWrite(sw, LOW);
  server.send(200, "text/html", "ocdi");
}
void yak(){
  digitalWrite(sw, HIGH);
  server.send(200, "text/html", "yandy");
}

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(Step, OUTPUT); //Step pin as output
  pinMode(Dir,  OUTPUT); //Direcction pin as output
  pinMode(sw,  OUTPUT);
  digitalWrite(Step, LOW); // Currently no stepper motor movement
  digitalWrite(Dir, LOW);
  digitalWrite(sw, LOW);
    



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
  server.on("/control/2", ocur);
  server.on("/control/3", yak);
  server.begin();
}
 
void loop() {
  server.handleClient();
}
