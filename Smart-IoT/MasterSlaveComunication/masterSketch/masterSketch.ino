#include <SoftwareSerial.h>
SoftwareSerial slaveLights (2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  slaveLights.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()!=0){
    slaveLights.write(Serial.read());
  }
  if(slaveLights.available()!=0){
    Serial.println(slaveLights.readStringUntil('\n'));
  }

}
