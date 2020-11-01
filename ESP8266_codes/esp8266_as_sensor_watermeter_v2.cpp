#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


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


// water sensor setup
volatile int flow_frequency; // Measures flow sensor pulses
unsigned int l_hour; // Calculated litres/hour
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;

void flow () // Interrupt function
{
   flow_frequency++;
}
//////


void handlePong() {
  server.send(200, "text/html", device_key);
}


void setup(){  
  // **** measurer setup **** //
  pinMode(flowsensor, INPUT);
  digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
  attachInterrupt(0, flow, RISING); // Setup Interrupt
  sei(); // Enable interrupts
  currentTime = millis();
  cloopTime = currentTime;
  // *********************** //

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
  currentTime = millis();
  if(currentTime >= (cloopTime + 5000))
  {
    cloopTime = currentTime; // Updates cloopTime
    // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
    l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
    flow_frequency = 0; // Reset Counter
    // Serial.print(l_hour, DEC); // Print litres/hour
    // Serial.println(" L/hour");

    String argument_data = "?device_key="+device_key+"&command="+command+"&value="+String(l_hour);
    sendRequest("http://"+serverUrl+"/esp/ArgToDB/",argument_data);
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