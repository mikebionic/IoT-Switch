#include <SoftwareSerial.h>
SoftwareSerial master_controller(2,3);
SoftwareSerial slave_controller(4,5);

int led = 13;

void setup() {
  Serial.begin(9600);
  master_controller.begin(9600);
  slave_controller.begin(9600);
  pinMode(led,OUTPUT);
}

void loop() {
  slave_controller.listen();
  if(Serial.available() != 0){
    String payload = Serial.readStringUntil('\n');
    payload.trim();
    if (payload.length()>0){

      if (payload == "heyhey"){
        digitalWrite(led, 1);
      }

      char* cString = (char*) malloc(sizeof(char)*(payload.length() + 1));
      payload.toCharArray(cString, payload.length() + 1);

      slave_controller.write(cString);
    }
  }

  if (slave_controller.available()){
    String data = slave_controller.readStringUntil('\n');
    data.trim();
    if (data.length() > 0){
      Serial.println(data);
      if (data == "off_called"){
        digitalWrite(led, 0);
      }
      if (data == "on_called"){
        digitalWrite(led, 1);
      }
    }
  }

}