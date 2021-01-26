#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

// int light1pin = 0; // D0
// int light2pin = 1; // D1
// int light3pin = 3; // D2
int buttonPin = 2;

int qtyOfPins = 3;
int pinsList[] = {0, 1, 3};
int pinStatesList[] = {0, 0, 0};

boolean ledState = false;
boolean buttonState = 1;
boolean lastButtonState = 1;

IPAddress staticIP(192, 168, 1, 209); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway) 
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "ssid";
const char* password = "password";
const char* deviceName = "Smart lights v2";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "lights_hash";

ESP8266WebServer server(80);

void handleDevice() {
  String pin1 = server.arg("pin1");
  String pin2 = server.arg("pin2");
  String pin3 = server.arg("pin3");

  pin1.trim();
  pin2.trim();
  pin3.trim();

  if(pin1 == "1"){
    pinStatesList[0] = 1;
  }
  else if(pin1 == "0"){
    pinStatesList[0] = 0;
  }
  if(pin2 == "1"){
    pinStatesList[1] = 1;
  }
  else if(pin2 == "0"){
    pinStatesList[1] = 0;
  }
  if(pin3 == "1"){
    pinStatesList[2] = 1;
  }
  else if(pin3 == "0"){
    pinStatesList[2] = 0;
  }

  updatePinStates();

  server.send(200, "text/html", "OK");
}

void updatePinStates(){
  for (int i = 0; i < qtyOfPins; i++){
    digitalWrite(pinsList[i], pinStatesList[i]);
  }
}

void handlePong() {
 server.send(200, "text/html", device_key);
}


void setup() {
  Serial.begin(115200);
  delay(10);

  for (int i = 0; i < qtyOfPins; i++){
    pinMode(pinsList[i], OUTPUT);
    digitalWrite(pinsList[i], 0);
  }

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
 
void loop() {
  server.handleClient();
  buttonStateChange();
}


boolean debounce(boolean lastState){
  boolean currentState = digitalRead(buttonPin);
  if (lastState != currentState){
    delay(5);
    currentState = digitalRead(buttonPin);
  }
  return currentState;
}

void buttonStateChange() {
  buttonState = debounce(lastButtonState);
  if (lastButtonState == 1 && buttonState == 0){
    ledState = !ledState;
    String argument_data = "?device_key="+device_key+"&state="+String(ledState);

    for (int i = 0; i < qtyOfPins; i++){
      pinStatesList[i] = ledState;
    }

    updatePinStates();

    sendRequest("http://"+serverUrl+"/esp/setState/",argument_data);
  }

  lastButtonState = buttonState;
  updatePinStates();
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

