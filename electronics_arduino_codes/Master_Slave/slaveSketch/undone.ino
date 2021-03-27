#include <SoftwareSerial.h>
SoftwareSerial master_controller(2,3);
SoftwareSerial slave_controller1(4,5);
SoftwareSerial slave_controller2(6,7);
SoftwareSerial slave_controller3(8,9);
SoftwareSerial slave_controller4(10,11);
SoftwareSerial slave_controller5(14,15);

int led = 13;

void setup() {
  Serial.begin(9600);
  master_controller.begin(9600);
  slave_controller1.begin(9600);
  slave_controller2.begin(9600);
  slave_controller3.begin(9600);
  slave_controller4.begin(9600);
  slave_controller5.begin(9600);
  pinMode(led,OUTPUT);
}

void loop() {
 if(master_controller.available()){
   String payload = master_controller.readStringUntil('\n');
   payload.trim();
   Serial.println(payload);
   if (payload.length()>0){
    if (payload == "heyhey"){
      digitalWrite(led, 1);
    }
   }
 }
}
