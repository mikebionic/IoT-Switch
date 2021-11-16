#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

IPAddress staticIP(192, 168, 1, 105);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);

const int ledPin = 2;

const char* ssid = "Smart_Gorjaw";
const char* password = "gorjaw@!85";
// access point!!
#define AP_SSID "ESP8266"
#define AP_PASS "magicword"

const char* deviceName = "light_control_UI";
String payload;
String device_key = "secret";
String command = "light_control_UI";
String validation_key = "key";

ESP8266WebServer server(80);

String control_input_on = "<input type=\"hidden\" name=\"control_input\" value=\"1\"></br>";
String submit_input_on = "<input type=\"submit\" style=\"border-radius: 50px 50px 50px 50px;text-align:center;height:150px;font-size:50px;width:400px;color:white;background-color: #00A8A9\" value=\"On\">";

String control_input_off = "<input type=\"hidden\" name=\"control_input\" value=\"0\"></br>";
String submit_input_off = "<input type=\"submit\" style=\"border-radius: 50px 50px 50px 50px;text-align:center;height:150px;font-size:50px;width:400px;color:white;background-color: #f15d3c\" value=\"Off\">";

String div_view = "<div>";
String form_view = "<form style=\"margin-top: 180px;display:flex;flex-direction: column;align-items: center;\" action=\"/ulanyjy\" method=\"POST\">";
String form_end_view = "</form>";
String div_end_view = "</div>";
String html_view = div_view + form_view + control_input_on + submit_input_on + form_end_view + form_view + control_input_off + submit_input_off + form_end_view + div_end_view;


void handlePong() {
  server.send(200, "text/html", device_key);
}


void handleRouteAction() {
  String command = server.arg("command");
  command.trim();
  
  if (command == "0") {
    Serial.println("Light is set 0");
    digitalWrite(ledPin, 0);
    server.send(200, "text/html", html_view);
  }
  else if (command == "1") {
    Serial.println("Light is set 1");
    digitalWrite(ledPin, 1);
    server.send(200, "text/html", html_view);
  }
  else {
    server.send(200, "text/html", html_view);
  }

  server.send(200, "text/html", "OK");
}

void handleRoot(){
  server.send(200, "text/html", html_view);
}

void handleFormSubmit(){
  if( !server.hasArg("control_input") || server.arg("control_input") == NULL) {
    server.send(200, "text/html", html_view);
    return;
  }
  if (server.arg("control_input") == "0") {
    Serial.println("Light is set 0");
    digitalWrite(ledPin, 0);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("control_input") == "1") {
    Serial.println("Light is set 1");
    digitalWrite(ledPin, 1);
    server.send(200, "text/html", html_view);
  }
  else {
    server.send(200, "text/html", html_view);
  }
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  WiFi.disconnect();
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);
   
  // Begin Access Point
  WiFi.mode(WIFI_AP_STA);
  // WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(AP_SSID, AP_PASS);
  // WiFi.softAP(AP_SSID, AP_PASS, AP_CHANNEL, AP_HIDDEN, AP_MAX_CON);
  WiFi.begin(ssid, password);

  delay(500);
  Serial.println(WiFi.localIP());

  pinMode(ledPin, OUTPUT);
  
  server.on("/ping/", handlePong);
  server.on("/control/", handleRouteAction);
  server.on("/validation/", handleRoot);
  server.on("/ulanyjy", handleFormSubmit);
  server.begin();
}

void loop() {
  server.handleClient();
}
