#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


//Static IP address configuration
IPAddress staticIP(192, 168, 1, 130); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "ssid";
const char* password = "password";
const char* deviceName = "Double_light_switch";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "dfj7sdsegf40dg";

#define LED1 0
#define LED2 1
#define SW 2

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


void buttonStateChange() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == 0) {
      counter++;
    }
    delay(50);
  }
  lastButtonState = buttonState;
  if (counter > 0) {
    digitalWrite(LED1, 1);
  }
  if (counter >= 2 ) {
    digitalWrite(LED2, 1);
  }
  if (counter >= 3){
    counter = 0;
  }
  else if (counter == 0){
    digitalWrite(LED2, 0);
    digitalWrite(LED1, 0);
  }
  String argument_data = "?device_key="+device_key+"&state="+String(ledState);
  sendRequest("http://"+serverUrl+"/esp/ArgToDB/",argument_data);

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
