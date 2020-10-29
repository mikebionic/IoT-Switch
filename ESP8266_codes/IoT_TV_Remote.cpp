#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <IRsend.h>
// Add this library: https://github.com/markszabo/IRremoteESP8266
#include <IRremoteESP8266.h>

#define IR_SEND_PIN 12
#define DELAY_BETWEEN_COMMANDS 1000
IRsend irsend(IR_SEND_PIN);

//Static IP address configuration
IPAddress staticIP(192, 168, 1, 176); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "ssid";
const char* password = "password";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "asdgdsf4567)N$3zx4a2";

ESP8266WebServer server(80);

const int led = BUILTIN_LED;


void handlePong(){
 server.send(200, "text/html", device_key);
}


void handleDevice(){
  String command = server.arg("command");

  command.trim();
  if (command.length() > 0){
    if (command == "down"){
      Serial.println("Sorround Sound Down");
      irsend.sendNEC(0x4BB6C03F, 32);
      server.send(200, "text/plain", "Volume Down");
    }

    if (command == "up"){
      Serial.println("Surround Sound Up");
      irsend.sendNEC(0x4BB640BF, 32);
      server.send(200, "text/plain", "Volume Up");
    }

    if (command == "sspower"){
      Serial.println("Surround Sound power");
      irsend.sendNEC(0x4B36D32C, 32);
      server.send(200, "text/plain", "Surround Sound Power");
    }

    if (command == "sschannel1"){
      Serial.println("Surround Sound Channel 1");
      irsend.sendNEC(0x4B3631CE, 32);
      server.send(200, "text/plain", "Surround Sound Channel 1");
    }

    if (command == "sschannel2"){
      Serial.println("Surround Sound Channel 2");
      irsend.sendNEC(0x4BB6F00F, 32);
      server.send(200, "text/plain", "Surround Sound Channel 2");
    }

    if (command == "sschannel3"){
      Serial.println("Surround Sound Channel 3");
      irsend.sendNEC(0x4BB6708F, 32);
      server.send(200, "text/plain", "Surround Sound Channel 3");
    }

    if (command == "sschannel4"){
      Serial.println("Surround Sound Channel 4");
      irsend.sendNEC(0x4BB6B04F, 32);
      server.send(200, "text/plain", "Surround Sound Channel 4");
    }

    if (command == "sstvsound"){
      Serial.println("Surround Sound sstvsound");
      irsend.sendNEC(0x4BB6906F, 32);
      server.send(200, "text/plain", "Surround Sound sstvsound");
    }

    if (command == "tvpower"){
      Serial.println("TV power");
      irsend.sendNEC(0x20DF10EF, 32);
      server.send(200, "text/plain", "TV Power");
    }

    if (command == "tvsource"){
      Serial.println("TV Source");
      irsend.sendNEC(0x20DFD02F, 32);
      server.send(200, "text/plain", "TV Source");
    }

    if (command == "togglesource"){
      Serial.println("TV Source");
      irsend.sendNEC(0x20DFD02F, 32);
      delay(DELAY_BETWEEN_COMMANDS);
      irsend.sendNEC(0x20DFD02F, 32);
      server.send(200, "text/plain", "TV Source");
    }

    if (command == "satpower"){
      Serial.println("Sat Power");
      irsend.sendNEC(0xA25D7887, 32);
      server.send(200, "text/plain", "Sat Power");
    }

    if (command == "satok"){
      Serial.println("Sat Ok");
      irsend.sendNEC(0xA25DFA05, 32);
      server.send(200, "text/plain", "Sat OK");
    }

    if (command == "satexit"){
      Serial.println("Sat Exit");
      irsend.sendNEC(0xA25D06F9, 32);
      server.send(200, "text/plain", "Sat Exit");
    }

    if (command == "satup"){
      Serial.println("Sat UP");
      irsend.sendNEC(0xA25DC03F, 32);
      server.send(200, "text/plain", "Sat UP");
    }

    if (command == "satdown"){
      Serial.println("Sat Down");
      irsend.sendNEC(0xA25D7A85, 32);
      server.send(200, "text/plain", "Sat Down");
    }

    if (command == "satblue"){
      Serial.println("Sat Blue");
      irsend.sendNEC(0xA25D52AD, 32);
      server.send(200, "text/plain", "Sat Blue");
    }

    if (command == "chromecast"){
      Serial.println("Chromecast");
      irsend.sendNEC(0x20DFD02F, 32);
      delay(DELAY_BETWEEN_COMMANDS);
      irsend.sendNEC(0x20DFD02F, 32);
      delay(DELAY_BETWEEN_COMMANDS);
      irsend.sendNEC(0x4BB6906F, 32);
      server.send(200, "text/plain", "Chromecast");
    }
  }
}


void setup(){
  irsend.begin();
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  Serial.begin(115200);
    
  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS Responder Started");
  }

  server.on("/ping/", handlePong);
  server.on("/control/", handleDevice);
  server.begin();
  Serial.println("HTTP Server Started");
}

void loop() {
  server.handleClient();
}