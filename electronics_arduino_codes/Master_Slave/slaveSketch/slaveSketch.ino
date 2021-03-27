#include <SoftwareSerial.h>
String stream;
int led = 13;
SoftwareSerial master (2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  master.begin(9600);
  pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (master.available()){
    stream = master.readStringUntil('\n');
    stream.trim();
    if (stream.length()>0){
      if (stream == "room1swON"){
        Serial.println("Swith of First Room");
        master.write("Switch of First Room");
        digitalWrite(led,1);
      }
      else if (stream == "room1swOFF"){
        Serial.println("Switch off");
        master.write("Switch off");
        digitalWrite(led,0);
      }
      Serial.println(stream);
      stream="";
    }
  }
}
