#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// water sensor setup
byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin1      = 2;
byte sensorInterrupt2 = 0;
byte sensorPin2      = 4;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;

volatile byte pulseCount;  
volatile byte pulseCount2;  

float flowRate;
float flowRate2;

unsigned int flowMilliLitres;
unsigned int flowMilliLitres2;
unsigned long totalMilliLitres;
unsigned long totalMilliLitres2;

unsigned long oldTime;
unsigned long pTime = 30000;
unsigned long oldTime2 = 0;
//////

//Static IP address configuration
IPAddress staticIP(192, 168, 1, 223); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "ssid";
const char* password = "password";
const char* deviceName = "Esp water meter";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "jbhbnefb63bno2u1";
String command = "water_measurer_sensor";

ESP8266WebServer server(80);


void handlePong() {
  server.send(200, "text/html", device_key);
}


void setup(){  
  pinMode(sensorPin1, INPUT);
  digitalWrite(sensorPin1, 1);
  pinMode(sensorPin2, INPUT);
  digitalWrite(sensorPin2, 1);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;

  pulseCount2        = 0;
  flowRate2          = 0.0;
  flowMilliLitres2   = 0;
  totalMilliLitres2  = 0;
  oldTime           = 0;

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
  if(millis() - oldTime2 >= 5000)
  {
    int value = totalMilliLitres/1000*2;
    int value2 = totalMilliLitres2/1000*2;
    unsigned int total_value = value + value2;

    String argument_data = "?device_key="+device_key+"&command="+command+"&value="+String(total_value);
    sendRequest("http://"+serverUrl+"/esp/ArgToDB/",argument_data);

    oldTime2 = millis();
    totalMilliLitres = 0;
    totalMilliLitres2 = 0;
  }
  if((millis() - oldTime) > 1000)    // Only process counters once per second
  {
    detachInterrupt(sensorInterrupt);
    detachInterrupt(sensorInterrupt2);

    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    flowRate2 = ((1000.0 / (millis() - oldTime)) * pulseCount2) / calibrationFactor;

    oldTime = millis();

    flowMilliLitres = (flowRate / 60) * 1000;
    flowMilliLitres2 = (flowRate2 / 60) * 1000;
    
    totalMilliLitres += flowMilliLitres;
    totalMilliLitres2 += flowMilliLitres2;
      
    unsigned int frac;
    
    pulseCount = 0;
    pulseCount2 = 0;
    
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    attachInterrupt(sensorInterrupt2, pulseCounter, FALLING);
  }
}


void pulseCounter()
{
  pulseCount++;
  pulseCount2++;
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