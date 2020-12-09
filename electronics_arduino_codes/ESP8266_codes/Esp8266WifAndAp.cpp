#include <ESP8266WiFi.h>
 
 
// Set WiFi credentials
#define WIFI_SSID "YOUR WIFI NETWORK SSID"
#define WIFI_PASS "YOUR WIFI PASSWORD"
 
// Set AP credentials
#define AP_SSID "ESP8266"
#define AP_PASS "magicword"
// #define AP_CHANNEL 1
// #define AP_HIDDEN true
// #define AP_MAX_CON 8
//
// Set Ip addresses
// IPAddress local_IP(192,168,4,22);
// IPAddress gateway(192,168,4,9);
// IPAddress subnet(255,255,255,0);



void setup()
{
  // Setup serial port
  Serial.begin(115200);
  Serial.println();
 
  // Begin Access Point
  WiFi.mode(WIFI_AP_STA);
  // WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_SSID, AP_PASS);
  // WiFi.softAP(AP_SSID, AP_PASS, AP_CHANNEL, AP_HIDDEN, AP_MAX_CON);

  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
 
  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
 
  // Connected to WiFi
  Serial.println();
  Serial.println("Connected!");
  Serial.print("IP address for network ");
  Serial.print(WIFI_SSID);
  Serial.print(" : ");
  Serial.println(WiFi.localIP());
  Serial.print("IP address for network ");
  Serial.print(AP_SSID);
  Serial.print(" : ");
  Serial.print(WiFi.softAPIP());
 
}
 
void loop() {
  // put your main code here, to run repeatedly:
  
}
