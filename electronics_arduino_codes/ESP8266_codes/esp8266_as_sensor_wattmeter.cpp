#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// wattmeter sensor setup
#include "ACS712.h"
int count = 0;
int interval = 30;
int myArray [30];
int sumP = 0;
unsigned long lastRef = 0;
ACS712 sensor(ACS712_30A, A0);
//////

//Static IP address configuration
IPAddress staticIP(192, 168, 1, 222); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "ssid";
const char* password = "password";
const char* deviceName = "Esp wattmeter";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "jbhbnefb63bno2u1";
String command = "watt_measurer_sensor";

ESP8266WebServer server(80);


void handlePong() {
  server.send(200, "text/html", device_key);
}


void setup(){
  sensor.calibrate();

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
 
  server.on("/ping/", handlePong);
 
  server.begin();
  Serial.println("HTTP server started");
}


void loop(){
  server.handleClient();
  measureAndSend();
}


void measureAndSend() {
  if (millis() - lastRef >= 1000){
    float U = 230;
    float I = sensor.getCurrentAC();
    if (I >= 0.06 && I <= 0.1) I = 0;
    float P = U * I;
    count += 1;
    myArray[count -1] = P;
    if (count == interval)
    {
      for (int i = 0; i <= interval-1; i++)
      {
        sumP += myArray[i];
      }
      String value = String(sumP);

      String argument_data = "?device_key="+device_key+"&command="+command+"&value="+String(value);
      sendRequest("http://"+serverUrl+"/esp/ArgToDB/",argument_data);

      count = 0;
      sumP = 0;
    }
    lastRef = millis();
  }
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

