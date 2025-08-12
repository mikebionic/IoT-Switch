#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);

int numRooms = 4;
int numLights= 4;
int numSockets = 3;
int lightStates[] = {0,0,0,0};
int roomSwitches[] = {4,5,6,7};
int room1Lights[] = {8,9,10,11};
int room2Lights[] = {12,13,14,15};
// int room3Lights[] = {16,17,18,19};
// int room4Lights[] = {20,21,22,23};

// int room1Sockets[] = {22,23,24};
// int room2Sockets[] = {25,26,27};
int state1[]={1,0,0,0};
int state2[]={1,1,0,0};
int state3[]={1,1,1,0};
int state4[]={1,1,1,1};
int allOff[]={0,0,0,0};

long secRoom1 = millis();
long secRoom2 = millis();
long secRoom3 = millis();
long secRoom4 = millis();

char queryRoom1 = '*';
char queryRoom2 = '*';
char queryRoom3 = '*';
char queryRoom4 = '*';

void setup(){
  Serial.begin(9600);
  int i;
  for(i=0;i<numRooms;i++){
    pinMode(roomSwitches[i],INPUT_PULLUP);
  }
  for(i=0;i<numLights;i++){
    pinMode(room1Lights[i],OUTPUT);
    pinMode(room2Lights[i],OUTPUT);
    // pinMode(room3Lights[i],OUTPUT);
    // pinMode(room4Lights[i],OUTPUT);
    digitalWrite(room1Lights[i],0);
    digitalWrite(room2Lights[i],0);
    // digitalWrite(room3Lights[i],0);
    // digitalWrite(room4Lights[i],0);
  }
}

void loop()
{
  queryRoom1 = '*';
  if(digitalRead(roomSwitches[1])==0){
    if((secRoom1+1000)<millis()){
      queryRoom1 = '1';
     }
     if((secRoom1+3000)>(secRoom1+1000) && (secRoom1+3000)<millis()){
      queryRoom1 = '2';
     }
     if((secRoom1+5000)>(secRoom1+3000) && (secRoom1+5000)<millis()){
      queryRoom1 = '3';
     }
     if((secRoom1+8000)>(secRoom1+5000) && (secRoom1+8000)<millis()){
       queryRoom1 = '4';
     }
     if((secRoom1+11000)<millis()||millis()<(secRoom1+1000)){
      queryRoom1 = '0';
     }
  }
  else if(digitalRead(roomSwitches[1]==1)){
    secRoom1 = millis();
  }
  switch(queryRoom1){
    case '1': changeState(room1Lights,state1);break;
    case '2': changeState(room1Lights,state2);break;
    case '3': changeState(room1Lights,state3);break;
    case '4': changeState(room1Lights,state4);break;
    case '0': changeState(room1Lights,allOff);break;
  }

  queryRoom2 = '*';
  if(digitalRead(roomSwitches[2])==0){
    if((secRoom2+1000)<millis()){
      queryRoom2 = '1';
     }
     if((secRoom2+3000)>(secRoom2+1000) && (secRoom2+3000)<millis()){
      queryRoom2 = '2';
     }
     if((secRoom2+5000)>(secRoom2+3000) && (secRoom2+5000)<millis()){
      queryRoom2 = '3';
     }
     if((secRoom2+8000)>(secRoom2+5000) && (secRoom2+8000)<millis()){
       queryRoom2 = '4';
     }
     if((secRoom2+11000)<millis()||millis()<(secRoom2+1000)){
      queryRoom2 = '0';
     }
  }
  else if(digitalRead(roomSwitches[2]==1)){
    secRoom2 = millis();
  }
  switch(queryRoom2){
    case '1': changeState(room2Lights,state1);break;
    case '2': changeState(room2Lights,state2);break;
    case '3': changeState(room2Lights,state3);break;
    case '4': changeState(room2Lights,state4);break;
    case '0': changeState(room2Lights,allOff);break;
  }
}

void changeState(int lightArray[],int modeArray[]){
  for(int i=0;i<numLights;i++){
    digitalWrite(lightArray[i],modeArray[i]);
  }
}
