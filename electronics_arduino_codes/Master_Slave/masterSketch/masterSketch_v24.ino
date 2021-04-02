#include <SoftwareSerial.h>
SoftwareSerial master_controller(2,3);
SoftwareSerial slave_controller1(4,5);
SoftwareSerial slave_controller2(6,7);
SoftwareSerial slave_controller3(8,9);
SoftwareSerial slave_controller4(10,11);
SoftwareSerial slave_controller5(14,15);

void setup() {
  Serial.begin(9600);
  master_controller.begin(9600);
  slave_controller1.begin(9600);
  slave_controller2.begin(9600);
  slave_controller3.begin(9600);
  slave_controller4.begin(9600);
  slave_controller5.begin(9600);
}

void loop() {
  if(Serial.available()!=0){
    String payload = Serial.readStringUntil('\n');
    payload.trim();
		if (payload.length()>0){

			char* cString = (char*) malloc(sizeof(char)*(payload.length() + 1));
			payload.toCharArray(cString, payload.length() + 1);
			
			slave_controller1.write(cString);
			slave_controller2.write(cString);
			slave_controller3.write(cString);
			slave_controller4.write(cString);
      slave_controller5.write(cString);
		}
  }

  if(slave_controller1.available()!=0){
    Serial.println(slave_controller1.readStringUntil('\n'));
  }

}