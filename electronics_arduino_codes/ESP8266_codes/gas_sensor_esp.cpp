#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

IPAddress staticIP(192, 168, 1, 145);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);

const char* ssid = "ssid";
const char* password = "password";
const char* deviceName = "Gas sensor";
String serverUrl = "192.168.1.252";
String payload;
String message;
String device_key = "gas_sensor_secret";

int signal_pin = 0;
int reset_pin = 2;
int current_signal_state = 0;
int last_signal_state = 0;
long off_time;
int gas_none_time = 4000;

ESP8266WebServer server(80);

void handleStatus() {
  server.send(200, "text/html", String(current_signal_state));
}

void handleReset() {
  call_reset();
  server.send(200, "text/html", "OK");
}

void handlePong() {
  server.send(200, "text/html", device_key);
}


void setup(void){
  pinMode(signal_pin, INPUT);
  pinMode(reset_pin, OUTPUT);
  digitalWrite(reset_pin, 0);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
 
  WiFi.mode(WIFI_STA);
  delay(500);
 
  server.on("/status", handleStatus);
  server.on("/control/1", handleReset);
  server.on("/ping/", handlePong);
  server.begin();
}

void loop(void){
  server.handleClient();
  int signal_state = digitalRead(signal_pin);
  check_signal_state(signal_state);
}


void check_signal_state(int signal_state){
  if (signal_state == 1){
    current_signal_state = 1;
    off_time = millis();
    message = "Gas exists";
    if (last_signal_state != current_signal_state){
      signalStateChange(current_signal_state);
    }
    last_signal_state = current_signal_state;

  }
  else {
    if (off_time + gas_none_time < millis()){
      current_signal_state = 0;
      message = "No gas detected";
      if (last_signal_state != current_signal_state){
        signalStateChange(current_signal_state);
      }
      last_signal_state = current_signal_state;
    }
  }
  return signal_state
}

void call_reset(){
  digitalWrite(reset_pin, 1);
  delay(100);
  digitalWrite(reset_pin, 0);
}



void signalStateChange(int state) {
  String argument_data = "?device_key="+device_key+"&state="+String(state);
  sendRequest("http://"+serverUrl+"/esp/setState/",argument_data);
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

