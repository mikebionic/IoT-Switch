#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <IRsend.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <ir_Samsung.h>



#define DELAY_BETWEEN_COMMANDS 1000
const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRSamsungAc ac(kIrLed);     // Set the GPIO used for sending messages.

//Static IP address configuration
IPAddress staticIP(192, 168, 1, 177); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "Smart_Gorjaw";
const char* password = "gorjaw@!85";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "alondatv2";
String command;
String action;

ESP8266WebServer server(80);

const int led = BUILTIN_LED;

void printState() {
  // Display the settings.
  Serial.println("Samsung A/C remote is in the following state:");
  Serial.printf("  %s\n", ac.toString().c_str());
}

void handlePong(){
 server.send(200, "text/html", device_key);
}


void handleDevice(){
  String command = server.arg("command");

  command.trim();
  if (command.length() > 0){
    if (command == "on"){
      ac.on();
      ac.send();
       printState();  
      server.send(200, "text/plain", "on");
    }
    if (command == "off"){
     ac.off();
     ac.send();
      server.send(200, "text/plain", "off");
    }
    if (command == "cool"){
     ac.setMode(kSamsungAcCool);
     ac.send();
      server.send(200, "text/plain", "cool");
    }
   if (command == "low"){
     ac.setFan(kSamsungAcFanLow);
     ac.send();
      server.send(200, "text/plain", "cool");
    }
    if (command == "high"){
     ac.setFan(kSamsungAcFanHigh);
     ac.send();
      server.send(200, "text/plain", "high");
    }
    if (command == "swingon"){
     ac.setSwing(true);
     ac.send();
      server.send(200, "text/plain", "swingon");
    }
     if (command == "swingoff"){
     ac.setSwing(false);
     ac.send();
      server.send(200, "text/plain", "swingoff");
    }
    if (command == "22"){
     ac.setTemp(22);
     ac.send();
      server.send(200, "text/plain", "22");
    }
    if (command == "23"){
     ac.setTemp(23);
     ac.send();
      server.send(200, "text/plain", "23");
    }
    if (command == "24"){
     ac.setTemp(24);
     ac.send();
      server.send(200, "text/plain", "24");
    }
    if (command == "25"){
     ac.setTemp(25);
     ac.send();
      server.send(200, "text/plain", "25");
    }
    if (command == "26"){
     ac.setTemp(26);
     ac.send();
      server.send(200, "text/plain", "26");
    }
    if (command == "27"){
     ac.setTemp(27);
     ac.send();
      server.send(200, "text/plain", "27");
    }
    if (command == "28"){
     ac.setTemp(28);
     ac.send();
      server.send(200, "text/plain", "28");
    }
    
  }
}


void setup(){
 ac.begin();

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

  if (Serial.available() != 0) {
    String stream = Serial.readStringUntil('\n');
    stream.trim();
    if (stream.length() > 0) {
      command = getStringPartByDelimeter(stream, ':', 0);
      action = getStringPartByDelimeter(stream, ':', 1);
      control_device(command, action);
    }
  }

}


void control_device(String command, String action) {
  if (action == "on"){
    ac.on();
    ac.send();
      printState();  
    server.send(200, "text/plain", "on");
  }
  if (action == "off"){
    ac.off();
    ac.send();
    server.send(200, "text/plain", "off");
  }
  if (action == "cool"){
    ac.setMode(kSamsungAcCool);
    ac.send();
    server.send(200, "text/plain", "cool");
  }
  if (action == "low"){
    ac.setFan(kSamsungAcFanLow);
    ac.send();
    server.send(200, "text/plain", "cool");
  }
  if (action == "high"){
    ac.setFan(kSamsungAcFanHigh);
    ac.send();
    server.send(200, "text/plain", "high");
  }
  if (action == "swingon"){
    ac.setSwing(true);
    ac.send();
    server.send(200, "text/plain", "swingon");
  }
    if (action == "swingoff"){
    ac.setSwing(false);
    ac.send();
    server.send(200, "text/plain", "swingoff");
  }
  if (action == "22"){
    ac.setTemp(22);
    ac.send();
    server.send(200, "text/plain", "22");
  }
  if (action == "23"){
    ac.setTemp(23);
    ac.send();
    server.send(200, "text/plain", "23");
  }
  if (action == "24"){
    ac.setTemp(24);
    ac.send();
    server.send(200, "text/plain", "24");
  }
  if (action == "25"){
    ac.setTemp(25);
    ac.send();
    server.send(200, "text/plain", "25");
  }
  if (action == "26"){
    ac.setTemp(26);
    ac.send();
    server.send(200, "text/plain", "26");
  }
  if (action == "27"){
    ac.setTemp(27);
    ac.send();
    server.send(200, "text/plain", "27");
  }
  if (action == "28"){
    ac.setTemp(28);
    ac.send();
    server.send(200, "text/plain", "28");
  }
}


String getStringPartByDelimeter(String data, char separator, int index) {
  int stringData = 0;
  String dataPart = "";
  for (int i = 0; i < data.length() - 1; i++) {
    if (data[i] == separator) {
      stringData++;
    } else if (stringData == index) {
      dataPart.concat(data[i]);
    } else if (stringData > index) {
      return dataPart;
      break;
    }
  }
  return dataPart;
}
