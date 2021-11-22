#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

IPAddress staticIP(192, 168, 1, 209); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway) 
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS

const char* ssid = "ssid";
const char* password = "password";
const char* deviceName = "IoT Device with setIP";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "some_IoT_Hash";

// access point!!
#define AP_SSID "ESP8266"
#define AP_PASS "magicword"


long setiptimeout = 15000; 
long current_time;


ESP8266WebServer server(80);

void handlePong() {
 server.send(200, "text/html", device_key);
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);

  // access point!!
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(AP_SSID, AP_PASS);
  WiFi.begin(ssid, password);
  ////

  delay(500);
  server.on("/ping/", handlePong);
  server.begin();

  sendRequest("?device_key=" + device_key);
  current_time = millis();
}
 
void loop() {
  server.handleClient();

  if (current_time + setiptimeout < millis()){
    sendRequest("?device_key=" + device_key);
    current_time = millis();
  }

}


void sendRequest(String path, String sendingData){
  if(WiFi.status()== WL_CONNECTED){
    String serverPath = path + sendingData;
    Serial.println(serverPath);
    payload = httpGETRequest(serverPath.c_str());
    Serial.println(payload);
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

String httpGETRequest(const char* serverName) {
  HTTPClient http;
  http.begin(serverName);
  int httpResponseCode = http.GET();  
  String payload = "{}"; 
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return payload;
}