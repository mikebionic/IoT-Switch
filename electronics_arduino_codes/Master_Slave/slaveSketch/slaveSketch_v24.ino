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
void send_uart_message(String payload, String receiver = "master"){
    char* cString = (char*) malloc(sizeof(char)*(payload.length() + 1));
  payload.toCharArray(cString, payload.length() + 1);
  if(receiver == "slave"){
      slave_controller.write(cString);
  }
  else if(receiver == "master"){
      master_controller.write(cString);
  }
}
void loop() {
  master_controller.listen();
 if(master_controller.available()){
     String payload = master_controller.readStringUntil('\n');
   payload.trim();
   Serial.println(payload);
   if (payload.length()>0){
      if (payload == "on_1"){
        digitalWrite(led, 1);
      send_uart_message("on_called", "master");
    }
    if (payload == "off_1"){
        digitalWrite(led, 0);
      send_uart_message("off_called", "master");
    }
   }
 }
}
