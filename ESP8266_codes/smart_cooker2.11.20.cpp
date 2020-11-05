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
const char* deviceName = "Siemens cooker";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "knb78G^n0sdf3foi";

ESP8266WebServer server(80);
/////////////

#include <SoftwareSerial.h>

int cooker1Pin = 16;
int cooker2Pin = 5;
int cooker3Pin = 4;
int cooker4Pin = 0;

bool old_state_manual = true;
int cookerPins[] = {16,5,4,0};
int numCookerPins = 4;
int powerPin = 2;
int auto_manual_selector_pin = 14;

long low_timingsList[] = {1000,50000,50000,47000,48000,38000,39000,35000,37000,32000,34000,28000,31000,20000,24000,9000,15000};
long high_timingsList[] = {0,1500,1500,4000,3000,5000,4000,8000,7000,11000,9000,15000,13000,23000,19000,35000,28000};
String selectorsList[] = {"0","1","1.","2","2.","3","3.","4","4.","5","5.","6","6.","7","7.","8","8."};
int selectorsQty = 17;

long high_millis1 = millis();
long low_millis1 = millis();

long high_millis2 = millis();
long low_millis2 = millis();

long high_millis3 = millis();
long low_millis3 = millis();

long high_millis4 = millis();
long low_millis4 = millis();


long pin1HighTime = 0;
long pin1LowTime = 0;

long pin2HighTime = 0;
long pin2LowTime = 0;

long pin3HighTime = 0;
long pin3LowTime = 0;

long pin4HighTime = 0;
long pin4LowTime = 0;


void set_timing1(String command){
  if (command == "9"){
    digitalWrite(cooker1Pin, 1);
    high_millis1 = millis();
    low_millis1 = millis();
    pin1LowTime = 0;
    pin1HighTime = 0;
  }
  else{
    for (int i=0; i<selectorsQty; i++){
      if (selectorsList[i] == command){
        high_millis1 = millis();
        pin1LowTime = low_timingsList[i];
        pin1HighTime = high_timingsList[i];
      }
    }
  }
}


void set_timing2(String command){
  if (command == "9"){
    digitalWrite(cooker2Pin, 1);
    high_millis2 = millis();
    low_millis2 = millis();
    pin2LowTime = 0;
    pin2HighTime = 0;
  }
  else{
    for (int i=0; i<selectorsQty; i++){
      if (selectorsList[i] == command){
        high_millis2 = millis();
        low_millis2 = millis();
        pin2LowTime = low_timingsList[i];
        pin2HighTime = high_timingsList[i];
      }
    }
  }
}


void set_timing3(String command){
  if (command == "9"){
    digitalWrite(cooker3Pin, 1);
    high_millis3 = millis();
    low_millis3 = millis();
    pin3LowTime = 0;
    pin3HighTime = 0;
  }
  else{
    for (int i=0; i<selectorsQty; i++){
      if (selectorsList[i] == command){
        high_millis3 = millis();
        low_millis3 = millis();
        pin3LowTime = low_timingsList[i];
        pin3HighTime = high_timingsList[i];
      }
    }
  }
}


void set_timing4(String command){
  if (command == "9"){
    digitalWrite(cooker4Pin, 1);
    high_millis4 = millis();
    low_millis4 = millis();
    pin4LowTime = 0;
    pin4HighTime = 0;
  }
  else{
    for (int i=0; i<selectorsQty; i++){
      if (selectorsList[i] == command){
        high_millis4 = millis();
        low_millis4 = millis();
        pin4LowTime = low_timingsList[i];
        pin4HighTime = high_timingsList[i];
      }
    }
  }
}


void handleDevice() {
  String cooker1 = server.arg("cooker1");
  String cooker2 = server.arg("cooker2");
  String cooker3 = server.arg("cooker3");
  String cooker4 = server.arg("cooker4");

  String power = server.arg("power");
  String auto_manual_selector = server.arg("auto_manual_switch");

  cooker1.trim();
  cooker2.trim();
  cooker3.trim();
  cooker4.trim();

  power.trim();
  auto_manual_selector.trim();

  if (cooker1.length() > 0){
    set_timing1(cooker1);
  }
  if (cooker2.length() > 0){
    set_timing2(cooker2);
  }
  if (cooker3.length() > 0){
    set_timing3(cooker3);
  }
  if (cooker4.length() > 0){
    set_timing4(cooker4);
  }

 //if(power == "1"){
 //   digitalWrite(powerPin,1);
 //   delay(2000);
 //   digitalWrite(auto_manual_selector_pin,0);
 // }
 // else if(power == "0"){
 //     digitalWrite(powerPin,0);
 // }

  if(auto_manual_selector == "auto"){
    digitalWrite(auto_manual_selector_pin,0);
    delay(2000);
    digitalWrite(powerPin,1);
    old_state_manual == false;
  }
  else if(auto_manual_selector == "manual"){
    if (old_state_manual == false){
      digitalWrite(powerPin,0);
      for (int i=0; i<numCookerPins; i++){
        digitalWrite(cookerPins[i],0);
      }
      pin1LowTime = low_timingsList[0];
      pin1HighTime = high_timingsList[0];
      pin2LowTime = low_timingsList[0];
      pin2HighTime = high_timingsList[0];
      pin3LowTime = low_timingsList[0];
      pin3HighTime = high_timingsList[0];
      pin4LowTime = low_timingsList[0];
      pin4HighTime = high_timingsList[0];
      delay(2000);
      digitalWrite(auto_manual_selector_pin,1);

      old_state_manual == true;
    }
  }

  server.send(200, "text/html", "OK");
}

void handlePong() {
 server.send(200, "text/html", device_key);
}

void setup(){
  for (int i=0; i<numCookerPins; i++){
    pinMode(cookerPins[i],OUTPUT);
    digitalWrite(cookerPins[i],0);
  }
  pinMode(powerPin,OUTPUT);
  pinMode(auto_manual_selector_pin,OUTPUT);
  digitalWrite(powerPin,0);
  digitalWrite(auto_manual_selector_pin,1);

  ////  Esp setup
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
  Pins();
}

void Pins(){
  if (high_millis1 + pin1HighTime > millis()){
    digitalWrite(cooker1Pin,1);
    low_millis1 = millis();
  }
  else if (high_millis1 + pin1HighTime < millis()){
    if (low_millis1 + pin1LowTime > millis()){
      digitalWrite(cooker1Pin,0);
    }
    else{
      high_millis1 = millis();
      low_millis1 = millis();
    }
  }

  if (high_millis2 + pin2HighTime > millis()){
    digitalWrite(cooker2Pin,1);
    low_millis2 = millis();
  }
  else if (high_millis2 + pin2HighTime < millis()){
    if (low_millis2 + pin2LowTime > millis()){
      digitalWrite(cooker2Pin,0);
    }
    else{
      high_millis2 = millis();
      low_millis2 = millis();
    }
  }

  if (high_millis3 + pin3HighTime > millis()){
    digitalWrite(cooker3Pin,1);
    low_millis3 = millis();
  }
  else if (high_millis3 + pin3HighTime < millis()){
    if (low_millis3 + pin3LowTime > millis()){
      digitalWrite(cooker3Pin,0);
    }
    else{
      high_millis3 = millis();
      low_millis3 = millis();
    }
  }

  if (high_millis4 + pin4HighTime > millis()){
    digitalWrite(cooker4Pin,1);
    low_millis4 = millis();
  }
  else if (high_millis4 + pin4HighTime < millis()){
    if (low_millis4 + pin4LowTime > millis()){
      digitalWrite(cooker4Pin,0);
    }
    else{
      high_millis4 = millis();
      low_millis4 = millis();
    }
  }

//   Serial.print(" ");
//   Serial.println(high_millis2);
//  Serial.print(cooker1Pin);
//  Serial.print(" ");
//  Serial.print(cooker2Pin);
//  Serial.print(" ");
//  Serial.print(cooker3Pin);
//  Serial.print(" ");
//  Serial.print(cooker4Pin);
//  Serial.println(" ");
}
