#include <SoftwareSerial.h>

String command;
int cooker1Pin = 13;
int cookerPins[] = {13,3,4,5};
int numCookerPins = 4;
int powerPin = 6;
int auto_manual_selector_pin = 7;

int low_timingsList[] = {50000,50000,47000,48000,38000,39000,35000,37000,32000,34000,28000,31000,20000,24000,9000,15000};
int high_timingsList[] = {1500,1500,4000,3000,5000,4000,8000,7000,11000,9000,15000,13000,23000,19000,35000,28000};
int selectorsList[] = {"1","1.","2","2.","3","3.","4","4.","5","5.","6","6.","7","7.","8","8."};
int selectorsQty = 16;

long high_millis = millis();
long low_millis = millis();

long pin1HighTime = millis();
long pin1LowTime = millis();

void setup(){
  Serial.begin(9600);
  for (int i=0; i<numCookerPins; i++){
    pinMode(cookerPins[i],OUTPUT);
    digitalWrite(cookerPins[i],0);
  }
  pinMode(powerPin,OUTPUT);
  pinMode(auto_manual_selector_pin,OUTPUT);
  digitalWrite(powerPin,0);
  digitalWrite(auto_manual_selector_pin,0);
}

void loop(){
  if (Serial.available() != 0){
    command = Serial.readStringUntil('/n');
    command.trim();
    if (command.length() > 0){
      set_timing(command);
    }
  }
  Pins();
}


void set_timing(String command){
  if (command == "9"){
    digitalWrite(cooker1Pin, 1);
  }
  else{
    for (int i=0; i<selectorsQty; i++){
       Serial.println(command);
      if (selectorsList[i]){
        int low_time_delay = low_timingsList[i];
        int high_time_delay = high_timingsList[i];
      }
    }
  }
}

void Pins(){
  if (high_millis + pin1HighTime > millis()){
    digitalWrite(cooker1Pin,1);
    low_millis = millis();
  }
  else if (high_millis + pin1HighTime < millis()){
    if (low_millis + pin1LowTime > millis()){
      digitalWrite(cooker1Pin,0);
    }
    else{
      high_millis = millis();
      low_millis = millis();
    }

  }
}