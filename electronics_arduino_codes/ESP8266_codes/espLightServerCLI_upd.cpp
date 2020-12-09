#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char MAIN_page[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html>
  <body>
  <center>
  <h1>WiFi LED on off demo: 1</h1><br>
  Ciclk to turn <a href="/control/1">LED ON</a><br>
  Ciclk to turn <a href="/control/0">LED OFF</a><br>
  <hr>
  </center>
  </body>
  </html>
)=====";

//Static IP address configuration
IPAddress staticIP(192, 168, 1, 145); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
 
const char* ssid = "ssid";
const char* password = "password";
const char* deviceName = "EspLights1";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "dfj7sdf40dg";

#define LED 2
#define SW 0

boolean ledState=false;
boolean buttonState=1;
boolean lastButtonState=1;

ESP8266WebServer server(80);


void handleRoot() {
 String s = MAIN_page;
 server.send(200, "text/html", s);
}

 
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
  digitalWrite(LED, LOW);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
 
  WiFi.mode(WIFI_STA);
 
//  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
//  }
 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", handleRoot);
  server.on("/control/1", handleLEDon);
  server.on("/control/0", handleLEDoff);
  server.on("/ping/", handlePong);
 
  server.begin();
  Serial.println("HTTP server started");
}
void loop(void){
  server.handleClient();
  buttonStateChange();
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
    sendRequest("http://"+serverUrl+"/esp/setState/",argument_data);
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

