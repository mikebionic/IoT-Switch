#include <SoftwareSerial.h>

String command;

int cooker1Pin = 13;
int cooker2Pin = 3;
int cooker3Pin = 4;
int cooker4Pin = 5;

int cookerPins[] = {13,3,4,5};
int numCookerPins = 4;
int powerPin = 6;
int auto_manual_selector_pin = 7;

long low_timingsList[] = {50000,50000,47000,48000,38000,39000,35000,37000,32000,34000,28000,31000,20000,24000,9000,15000};
long high_timingsList[] = {1500,1500,4000,3000,5000,4000,8000,7000,11000,9000,15000,13000,23000,19000,35000,28000};
String selectorsList[] = {"1","1.","2","2.","3","3.","4","4.","5","5.","6","6.","7","7.","8","8."};
int selectorsQty = 16;

long high_millis1 = millis();
long low_millis1 = millis();

long high_millis2 = millis();
long low_millis2 = millis();

long high_millis3 = millis();
long low_millis3 = millis();

long high_millis4 = millis();
long low_millis4 = millis();


long pin1HighTime = millis();
long pin1LowTime = millis();

long pin2HighTime = millis();
long pin2LowTime = millis();

long pin3HighTime = millis();
long pin3LowTime = millis();

long pin4HighTime = millis();
long pin4LowTime = millis();

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


void set_timing1(String command){
  if (command == "9"){
    digitalWrite(cooker1Pin, 1);
	  high_millis1 = millis();
  	low_millis1 = millis();
		pin1LowTime = 0;
		pin1HighTime = 0;
  }
  else{
    for (int i=0; i<selectorsQty; i++){
      // Serial.println(command);
      if (selectorsList[i] == command){
      	high_millis1 = millis();
				low_millis1 = millis();
        // long low_time_delay = low_timingsList[i];
        // long high_time_delay = high_timingsList[i];
        pin1LowTime = low_timingsList[i];
        pin1HighTime = high_timingsList[i];
      }
    }
  }
}


void set_timing2(String command){
  if (command == "9"){
    digitalWrite(cooker2Pin, 1);
	  high_millis2 = millis();
  	low_millis2 = millis();
		pin2LowTime = 0;
		pin2HighTime = 0;
  }
  else{
    for (int i=0; i<selectorsQty; i++){
      // Serial.println(command);
      if (selectorsList[i] == command){
      	high_millis2 = millis();
				low_millis2 = millis();
        // long low_time_delay = low_timingsList[i];
        // long high_time_delay = high_timingsList[i];
        pin2LowTime = low_timingsList[i];
        pin2HighTime = high_timingsList[i];
      }
    }
  }
}


void set_timing3(String command){
  if (command == "9"){
    digitalWrite(cooker3Pin, 1);
	  high_millis3 = millis();
  	low_millis3 = millis();
		pin3LowTime = 0;
		pin3HighTime = 0;
  }
  else{
    for (int i=0; i<selectorsQty; i++){
      // Serial.println(command);
      if (selectorsList[i] == command){
      	high_millis3 = millis();
				low_millis3 = millis();
        // long low_time_delay = low_timingsList[i];
        // long high_time_delay = high_timingsList[i];
        pin3LowTime = low_timingsList[i];
        pin3HighTime = high_timingsList[i];
      }
    }
  }
}


void set_timing4(String command){
  if (command == "9"){
    digitalWrite(cooker4Pin, 1);
	  high_millis4 = millis();
  	low_millis4 = millis();
		pin4LowTime = 0;
		pin4HighTime = 0;
  }
  else{
    for (int i=0; i<selectorsQty; i++){
      // Serial.println(command);
      if (selectorsList[i] == command){
      	high_millis4 = millis();
				low_millis4 = millis();
        // long low_time_delay = low_timingsList[i];
        // long high_time_delay = high_timingsList[i];
        pin4LowTime = low_timingsList[i];
        pin4HighTime = high_timingsList[i];
      }
    }
  }
}


////////////////

void Pins(){
  if (high_millis1 + pin1HighTime > millis()){
    digitalWrite(cooker1Pin,1);
    low_millis1 = millis();
  }
  else if (high_millis1 + pin1HighTime < millis()){
    if (low_millis1 + pin1LowTime > millis()){
      digitalWrite(cooker1Pin,0);
    }
    else{
      high_millis1 = millis();
      low_millis1 = millis();
    }
  }



  if (high_millis2 + pin2HighTime > millis()){
    digitalWrite(cooker2Pin,1);
    low_millis2 = millis();
  }
  else if (high_millis2 + pin2HighTime < millis()){
    if (low_millis2 + pin2LowTime > millis()){
      digitalWrite(cooker2Pin,0);
    }
    else{
      high_millis2 = millis();
      low_millis2 = millis();
    }
  }



  if (high_millis3 + pin3HighTime > millis()){
    digitalWrite(cooker3Pin,1);
    low_millis3 = millis();
  }
  else if (high_millis3 + pin3HighTime < millis()){
    if (low_millis3 + pin3LowTime > millis()){
      digitalWrite(cooker3Pin,0);
    }
    else{
      high_millis3 = millis();
      low_millis3 = millis();
    }
  }



  if (high_millis4 + pin4HighTime > millis()){
    digitalWrite(cooker4Pin,1);
    low_millis4 = millis();
  }
  else if (high_millis4 + pin4HighTime < millis()){
    if (low_millis4 + pin4LowTime > millis()){
      digitalWrite(cooker4Pin,0);
    }
    else{
      high_millis4 = millis();
      low_millis4 = millis();
    }
  }

  // Serial.print(low_millis);
  // Serial.print(" ");
  // Serial.println(high_millis);
  Serial.print(cooker1Pin);
  Serial.print(" ");
  Serial.print(cooker2Pin);
  Serial.print(" ");
  Serial.print(cooker3Pin);
  Serial.print(" ");
  Serial.print(cooker4Pin);
  Serial.println(" ");
}