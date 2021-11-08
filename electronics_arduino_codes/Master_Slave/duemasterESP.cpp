#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

IPAddress staticIP(192, 168, 1, 253);
IPAddress gateway(192, 168, 1, 1); 
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);


 // http://192.168.1.101/control/?command=led13&action=on&process_key=main_arduino_process_secret_key
const char* ssid = "Smart_Gorjaw";
const char* password = "gorjaw@!85";
const char* deviceName = "master_esp";
String serverUrl = "192.168.1.252";
String device_key = "ESP_ARDU_MASTER";
String command = "esp_communicator_secret";

String payload; // data combined to send to arduino
String stream; // data got from arduino to record on server

ESP8266WebServer server(80);

void sendFromUART(String command, String action, String process_key){
  String payload = command + ":" + action + ":" + process_key + ":";
  Serial.println(payload);
}

void handleDevice() {
  String command = server.arg("command");
  String action = server.arg("action");
  String process_key = server.arg("process_key");
  command.trim();
  action.trim();
  process_key.trim();

  sendFromUART(command, action, process_key);

  server.send(200, "text/html", "OK");
}

void handlePong() {
 server.send(200, "text/html", device_key);
}

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  WiFi.disconnect();
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  delay(500);

  // Serial.print(WiFi.localIP());
  server.on("/ping/", handlePong);
  server.on("/control/", handleDevice);
  server.begin();
}

void loop(){
  server.handleClient();
  sendDataFromMaster();
}


void sendDataFromMaster(){
  stream = "";
  if (Serial.available() != 0){
    stream = Serial.readStringUntil('\n');
    stream.trim();
    if (stream.length() > 0){
      Serial.println(stream);
      // String argument_data = "?device_key="+device_key+"&command="+command+"&value="+String(stream);
      // // we will provide command=somecommand&value=somevalue from stream
      if (stream.length() > 20){
        String argument_data = "?device_key="+device_key+"&"+String(stream)+"&isMaster=1";
        sendRequest("http://"+serverUrl+"/esp/ArgToDB/",argument_data); 
      }
    }
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
  if (httpResponseCode > 0){
    payload = http.getString();
  }
  http.end();
  return payload;
}
