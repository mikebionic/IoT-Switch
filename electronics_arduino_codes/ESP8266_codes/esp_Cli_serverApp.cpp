#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
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
IPAddress staticIP(192, 168, 1, 101); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
 
const char* ssid = "ssid";
const char* password = "password";
const char* deviceName = "EspLights1";

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

void setup(void){
  pinMode(LED, OUTPUT);
  pinMode(SW, INPUT);
  digitalWrite(LED, ledState);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
 
  WiFi.mode(WIFI_STA);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", handleRoot);
  server.on("/control/1", handleLEDon);
  server.on("/control/0", handleLEDoff);
 
  server.begin();
  Serial.println("HTTP server started");
}
void loop(void){
  server.handleClient();
  buttonStateChange();
}

boolean debounce(boolean last)
{
  boolean cur=digitalRead (SW);
  if (last!=cur);
  {
    delay(5);
    cur=digitalRead (SW);
  }
  return cur;
}

void buttonStateChange() {
  
  buttonState = debounce(lastButtonState);
  
  if (lastButtonState==1 && buttonState==0){
    ledState =! ledState;  
  }
  lastButtonState = buttonState;
  digitalWrite (LED, ledState);
 }
