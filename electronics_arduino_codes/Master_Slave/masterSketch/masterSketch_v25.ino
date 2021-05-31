#include <SoftwareSerial.h>

int led = 13;
String arduino_process_key = "main_arduino_process_secret_key";
String command = "";
String action = "";
String process_key = "";

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
}

void loop() {
  if(Serial.available() != 0){
    String stream = Serial.readStringUntil('\n');
    stream.trim();
    if (stream.length()>0){
      command = getStringPartByDelimeter(stream,':',0);
      action = getStringPartByDelimeter(stream,':',1);
      process_key = getStringPartByDelimeter(stream,':',2);

      if (process_key == arduino_process_key){
        control_device(command, action);
      }

    }
  }
}


String getStringPartByDelimeter(String data, char separator, int index){
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

void control_device(String command, String action){
  if (command == "led13"){
    if (action == "on"){
      digitalWrite(led, 1);
    }
    else if (action == "off"){
      digitalWrite(led, 0);
    }
  }
}