// /// Esp setup ///
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


IPAddress staticIP(192, 168, 1, 154); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway) 
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "ssid";
const char* password = "password";
const char* deviceName = "master_esp";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "master_esp_secret";

ESP8266WebServer server(80);

#include <SoftwareSerial.h>

void handleDevice() {
  String command = server.arg("command");
  String action = server.arg("action");
  command.trim();
	action.trim();

	// slave send here

  server.send(200, "text/html", "OK");
}

void handlePong() {
 server.send(200, "text/html", device_key);
}

void setup(){
  Serial.begin(115200);
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

void loop(){
  server.handleClient();
}
