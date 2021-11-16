#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>

IPAddress staticIP(192, 168, 1, 105);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(8, 8, 8, 8);

const int ledPin = 15;
int brightness1 = 62;
int brightness2 = 124;
int brightness3 = 186;
int brightness4 = 254;

const char* ssid = "Smart_Gorjaw";
const char* password = "gorjaw@!85";
const char* deviceName = "Dimmer";
String payload;
String device_key = "secret";
String command = "dimmer";
String validation_key = "key";

ESP8266WebServer server(80);

String dimmer_input = "<input style=\"height: 200px;width: 600px;font-size: 50px;\" type=\"text\" name=\"dimmer_input\" placeholder=\"ID Key\"></br>";
String submit_input = "<input type=\"submit\" style=\"border-radius: 50px 50px 50px 50px;text-align:center;height:150px;font-size:50px;width:400px;color:white;background-color: #00A8A9\" value=\"Validate\">";


String div_view = "<div>";
String form_view = "<form style=\"margin-top: 180px;display:flex;flex-direction: column;align-items: center;\" action=\"/ulanyjy\" method=\"POST\">";
String form_end_view = "</form></div>";
String html_view = div_view + form_view + dimmer_input + submit_input + form_end_view;


void handlePong() {
  server.send(200, "text/html", device_key);
}


void handleRouteAction() {
  String command = server.arg("command");
  command.trim();
  
  if (command == "0") {
    Serial.println("Dimmer is set 0");
    digitalWrite(ledPin, 0);
    server.send(200, "text/html", html_view);
  }
  else if (command == "1") {
    Serial.println("Dimmer is set 1");
    analogWrite(ledPin, brightness1);
    server.send(200, "text/html", html_view);
  }
  else if (command == "2") {
    Serial.println("Dimmer is set 2");
    analogWrite(ledPin, brightness2);
    server.send(200, "text/html", html_view);
  }
  else if (command == "3") {
    Serial.println("Dimmer is set 3");
    analogWrite(ledPin, brightness3);
    server.send(200, "text/html", html_view);
  }
  else if (command == "4") {
    Serial.println("Dimmer is set 4");
    analogWrite(ledPin, brightness4);
    server.send(200, "text/html", html_view);
  }

  server.send(200, "text/html", "OK");
}

void handleRoot(){
  server.send(200, "text/html", html_view);
}

void handleFormSubmit(){
  if( !server.hasArg("dimmer_input") || server.arg("dimmer_input") == NULL) {
    server.send(200, "text/html", html_view);
    return;
  }
  if (server.arg("dimmer_input") == "0") {
    Serial.println("Dimmer is set 0");
    digitalWrite(ledPin, 0);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("dimmer_input") == "1") {
    Serial.println("Dimmer is set 1");
    analogWrite(ledPin, brightness1);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("dimmer_input") == "2") {
    Serial.println("Dimmer is set 2");
    analogWrite(ledPin, brightness2);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("dimmer_input") == "3") {
    Serial.println("Dimmer is set 3");
    analogWrite(ledPin, brightness3);
    server.send(200, "text/html", html_view);
  }
  else if (server.arg("dimmer_input") == "4") {
    Serial.println("Dimmer is set 4");
    analogWrite(ledPin, brightness4);
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
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
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
