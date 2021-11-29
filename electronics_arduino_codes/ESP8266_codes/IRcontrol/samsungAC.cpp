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
  /*Serial.begin(115200);
  delay(200);

  // Set up what we want to send. See ir_Samsung.cpp for all the options.
  Serial.println("Default state of the remote.");
  printState();
  Serial.println("Setting initial state for A/C.");
  ac.off();
  ac.setFan(kSamsungAcFanLow);
  ac.setMode(kSamsungAcCool);
  ac.setTemp(25);
  ac.setSwing(false);
  printState();
*/
 
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
