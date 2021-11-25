#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

//Static IP address configuration
IPAddress staticIP(192, 168, 1, 130); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
 
const char* ssid = "Smart_Gorjaw";
const char* password = "gorjaw@!85";
const char* deviceName = "EspLights1";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "waterpump";

// access point!!
#define AP_SSID "ESP8266"
#define AP_PASS "magicword"


long setiptimeout = 15000; 
long current_time;

#define LED 2
#define SW 0

boolean ledState=false;
boolean buttonState=1;
boolean lastButtonState=1;

ESP8266WebServer server(80);
 

void handleLEDon() {
  ledState = 1;
  digitalWrite(LED,ledState);
  server.send(200, "text/html", "LED is ON");
}

 
void handleLEDoff() {
  ledState = 0;
  digitalWrite(LED,ledState);
  server.send(200, "text/html", "LED is OFF");
}


void handlePong() {
  server.send(200, "text/html", device_key);
}


void setup(void){
  pinMode(LED, OUTPUT);
  pinMode(SW, INPUT);
  digitalWrite(LED, 0);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);
 
 // access point!!
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(AP_SSID, AP_PASS);
  WiFi.begin(ssid, password);
  ////
 
//  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
//  }
 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/control/1", handleLEDon);
  server.on("/control/0", handleLEDoff);
  server.on("/ping/", handlePong);
 
  server.begin();
  Serial.println("HTTP server started");
  
  sendRequest("http://"+serverUrl+"/set-ip/", "?device_key=" + device_key);
  current_time = millis();
}


void loop(void){
  server.handleClient();
  buttonStateChange();
  
  if (current_time + setiptimeout < millis()){
    sendRequest("http://"+serverUrl+"/set-ip/", "?device_key=" + device_key);
    current_time = millis();
  }
  
}

boolean debounce(boolean last)
{
  boolean cur=digitalRead(SW);
  if (last!=cur);
  {
    delay(5);
    cur=digitalRead(SW);
  }
  return cur;
}

void buttonStateChange() {
  buttonState = debounce(lastButtonState);
  if (lastButtonState==1 && buttonState==0){
    ledState =! ledState;
    String argument_data = "?device_key="+device_key+"&state="+String(ledState);
    digitalWrite(LED, ledState);
    sendRequest("http://"+serverUrl+"/esp/detectWater/",argument_data);
  }
  lastButtonState = buttonState;
  digitalWrite(LED, ledState);
}

void sendRequest(String path, String sendingData){
  if(WiFi.status()== WL_CONNECTED){
    String serverPath = path+sendingData;
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

