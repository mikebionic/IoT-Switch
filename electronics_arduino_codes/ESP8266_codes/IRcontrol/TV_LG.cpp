 #include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266mDNS.h>
#include <IRsend.h>
// Add this library: https://github.com/markszabo/IRremoteESP8266
#include <IRremoteESP8266.h>

#define IR_SEND_PIN 4
#define DELAY_BETWEEN_COMMANDS 1000
IRsend irsend(IR_SEND_PIN);

//Static IP address configuration
IPAddress staticIP(192, 168, 1, 17); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "Smart_Gorjaw";
const char* password = "gorjaw@!85";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "alondatv1";

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
      irsend.sendNEC(0xE0E08679   , 32);
      server.send(200, "text/plain", "Volume Down");
    }

    if (command == "up"){
      Serial.println("Surround Sound Up");
      irsend.sendNEC(0xE0E006F9, 32);
      server.send(200, "text/plain", "Volume Up");
    }
    if (command == "satok"){
      Serial.println("Sat Ok");
      irsend.sendNEC(0xE0E016E9, 32);
      server.send(200, "text/plain", "Sat OK");
    }
    if (command == "tvpower"){
      Serial.println("TV power");
      irsend.sendNEC(0xE0E040BF, 32);
      server.send(200, "text/plain", "TV Power");
    }
 if (command == "mute"){
      Serial.println("mute");
      irsend.sendNEC(0xE0E0F00F, 32);
      server.send(200, "text/plain", " mute");
    }
    if (command == "volumedown"){
      Serial.println("volumedown");
      irsend.sendNEC(0xE0E0D02F, 32);
      server.send(200, "text/plain", "volumedown");
    }
 
   if (command == "upvolume"){
      Serial.println("volumeup");
      irsend.sendNEC(0xE0E0E01F, 32);
      server.send(200, "text/plain", "volumedown");
    }

    if (command == "menu"){
      Serial.println("menu");
      irsend.sendNEC(0xE0E058A7, 32);
      server.send(200, "text/plain", "menu");
    }

    if (command == "exit"){
      Serial.println("exit");
      irsend.sendNEC(0xE0E0B44B, 32);
      server.send(200, "text/plain", "exit");
    }

    if (command == "right"){
      Serial.println("Surround Sound Channel 3");
      irsend.sendNEC(0xE0E046B9, 32);
      server.send(200, "text/plain", "Surround Sound Channel 3");
    }

    if (command == "left"){
      Serial.println("Surround Sound Channel 4");
      irsend.sendNEC(0xE0E0A659, 32);
      server.send(200, "text/plain", "Surround Sound Channel 4");
    
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
