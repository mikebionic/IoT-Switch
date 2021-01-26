#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


int sock2pin = 0; // D0
int sock1pin = 1; // D1
int sock3pin = 2; // D2

IPAddress staticIP(192, 168, 1, 144); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway) 
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "ssid";
const char* password = "password";
const char* deviceName = "Smart socket";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "socket_hash";

ESP8266WebServer server(80);

void handleDevice() {
  String socket1 = server.arg("socket1");
  String socket2 = server.arg("socket2");
  String socket3 = server.arg("socket3");

  socket1.trim();
  socket2.trim();
  socket3.trim();

    if(socket1 == "1"){
        digitalWrite(sock1pin,1);
    }
    else if(socket1 == "0"){
        digitalWrite(sock1pin,0);
    }
    if(socket2 == "1"){
        digitalWrite(sock2pin,1);
    }
    else if(socket2 == "0"){
        digitalWrite(sock2pin,0);
    }
    if(socket3 == "1"){
        digitalWrite(sock3pin,1);
    }
    else if(socket3 == "0"){
        digitalWrite(sock3pin,0);
    }
  server.send(200, "text/html", "OK");
}


void handlePong() {
 server.send(200, "text/html", device_key);
}


void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(sock1pin, OUTPUT);
  pinMode(sock2pin, OUTPUT);
  pinMode(sock3pin, OUTPUT);


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
  server.on("/ping/", handlePong);
  server.on("/control/", handleDevice);
  server.begin();
}
 
void loop() {
  server.handleClient();
}
