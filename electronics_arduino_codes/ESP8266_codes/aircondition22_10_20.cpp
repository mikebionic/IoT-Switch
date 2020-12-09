#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

long x=millis();

int low = 16; // D0
int med = 5; // D1
int high = 4; // D2
int tel = 0; // D3
int actuatorRelay = 14;  // D5
int actuatorRelay2 = 12; // D6
String stream;


int ThermistorPin = A0;

float baselineTemp = 10.0;
int Vo;

float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int settedTemp=10.0;
bool settedTempActive = true;
bool done = false;
String action;
String val;


IPAddress staticIP(192, 168, 1, 243); //ESP static ip
IPAddress gateway(192, 168, 1, 1);   //IP Address of your WiFi Router (Gateway) 
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
IPAddress dns(8, 8, 8, 8);  //DNS
 
const char* ssid = "azat";
const char* password = "oguzhan85";
const char* deviceName = "Smartconditioner";
String serverUrl = "192.168.1.252";
String payload;
String device_key = "conD9mdc73om934";

ESP8266WebServer server(80);
/*void handleRoot() {
 String s = MAIN_page;
 server.send(200, "text/html", s);
}*/
void handleConditioner() {
  String stream = server.arg("command");
  Serial.println("Command is: " + stream);
  stream.trim();
//  if (stream.length()>0){
    action = getStringPartByNr(stream,':',0);
    val = getStringPartByNr(stream,':',1);
    settedTemp = val.toInt();
    if(action=="heater"){
      Serial.println("heater mode: ");
      Serial.println(settedTemp);
      settedTempActive=true;
    }
    if(action=="cooler"){
      Serial.println("cooler mode: ");
      Serial.println(settedTemp);
      settedTempActive=true;
    }
    else if(stream == "MED"){
      digitalWrite(med,1);
      digitalWrite(low,0);
      digitalWrite(high,0);
      Serial.println("MED");
    }
    else if(stream == "LOW"){
      digitalWrite(low,1);
      digitalWrite(med,0);
      digitalWrite(high,0);
      Serial.println("low");
    }
    else if(stream == "HIGH"){
      digitalWrite(high,1);
      digitalWrite(low,0);
      digitalWrite(med,0);
      Serial.println("high");
    }
   /* else if(stream == "telon"){
      digitalWrite(tel,1);
      Serial.println("telon");
    }
    else if(stream == "teloff"){
      digitalWrite(tel,0);
      Serial.println("teloff");
    }*/
      
    if(stream == "manualMode"){
      settedTempActive=false;
      digitalWrite(tel,1);
      digitalWrite(high,0);
      digitalWrite(low,0);
      digitalWrite(med,0);
      Serial.println("manualMode");
    }
    if(stream == "autoMode"){
      settedTempActive=true;
      Serial.println("autoMode");
    }
//  }

  server.send(200, "text/html", stream);
  stream="";
}
void handlePong() {
 server.send(200, "text/html", device_key);
} 
void returnTemp() {
 server.send(200, "text/html", "{temperature:"+String(Tc)+", setted:"+String(settedTemp)+"}");
} 

void setup() {
  Serial.begin(115200);
  delay(10);
  
  pinMode(actuatorRelay, OUTPUT);
  pinMode(actuatorRelay2, OUTPUT);
  pinMode(tel, OUTPUT);
  pinMode(med, OUTPUT);
  pinMode(low, OUTPUT);
  pinMode(high, OUTPUT);


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
  server.on("/conditioner/", handleConditioner);
  server.on("/checkTemp/", returnTemp);
  server.begin();
}
 
void loop() {
  server.handleClient();  
  controlTemp();
  temp();
}


void controlTemp(){
  if(settedTempActive==true){
    done = false;
    digitalWrite(actuatorRelay, 1);
    digitalWrite(actuatorRelay2, 1);
    if(action=="cooler"){
      if(done==false){
        if(Tc<settedTemp){
          Serial.println("cooling done");
          digitalWrite(actuatorRelay, 0);
          digitalWrite(actuatorRelay2, 0);
          done=true;
        }
      }
      if(Tc>settedTemp+2){
        done=false;
      }
    }
    if(action=="heater"){
      if(done==false){
        if(Tc>settedTemp){
          digitalWrite(actuatorRelay, 0);
          digitalWrite(actuatorRelay2, 0);
          done=true;
        }
      }
      if(Tc<settedTemp-2){
        done=false;
      }
    }
  }
  else if(settedTempActive==false){
    digitalWrite(actuatorRelay, 0);
    digitalWrite(actuatorRelay2, 0);
  }
}


void temp(){
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0)/ 5.0 + 32.0;
  // Serial.println(T);
   Serial.print("Temperature: "); 
  
  // Serial.print(Tf);
  // Serial.println(" F; ");
   Serial.print(Tc);
   Serial.println(" C");
   delay(2000);
}

//////// splitting text by delimeter : /////
String getStringPartByNr(String data, char separator, int index){
    int stringData = 0;
    String dataPart = "";
    for(int i = 0; i<data.length()-1; i++){
      if(data[i]==separator) {
        stringData++;
      }else if(stringData==index) {
        dataPart.concat(data[i]);
      }else if(stringData>index){
        return dataPart;
        break;
      }
    }
    return dataPart;
}
