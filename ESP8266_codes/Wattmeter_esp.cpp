#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include "ACS712.h"

int count = 0;
int interval = 30;
int myArray [30];
int sumP = 0;
unsigned long lastRef = 0;
ACS712 sensor(ACS712_30A, A0);

const char* ssid = "ssid";
const char* password = "password";

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

IPAddress staticIP(192, 168, 1, 130); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
int value;
String jsonBuffer;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP Address: ");
  Serial.println(WiFi.localIP());

  // **** measurer setup **** //
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
  Serial.begin(9600);
  attachInterrupt(0, flow, RISING); // Setup Interrupt
  sei(); // Enable interrupts
  currentTime = millis();
  cloopTime = currentTime;
  // *********************** //

}

void loop() {
  if(WiFi.status()== WL_CONNECTED){
    measureWatt()
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

void measureWatt(){
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
    String myString = String(sumP);
    Serial.println(myString);
    count = 0;
    sumP = 0;
    String serverPath = "http://"+serverUrl+"/"+apiKey+"/"+myString;
      
    jsonBuffer = httpGETRequest(serverPath.c_str());
    Serial.println(jsonBuffer);

    JSONVar myObject = JSON.parse(jsonBuffer);

    if (JSON.typeof(myObject) == "undefined") {
      Serial.println("Parsing input failed!");
      return;
    }
    if (myObject["status"]=="OK"){
      flow_frequency = 0;
    }

  }
}
