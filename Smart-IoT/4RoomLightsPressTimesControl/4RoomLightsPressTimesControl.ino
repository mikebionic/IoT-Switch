/*
 ---------------------------------------------------------
  The functioning and eas appendable sketch for room lights press control
  Coded with love by Muhammed aka mike-bionic
  --------------------------------------------------------
*/

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
int roomQueries[] = {1,2,3,4};


// Variables will change:
int buttonPushCounter[] = {0,0,0,0};
int buttonState[] = {1,1,1,1};
int lastButtonState[] = {1,1,1,1};
///////////////
int i;

void setup(){
  Serial.begin(9600);
  Serial.println("Coded with love by Muhammed aka mike-bionic");
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
  queryRoom1 = '0';
  }
}

void loop()
{
  for(i=0;i<numRooms;i++){
    buttonState[i] = digitalRead(roomSwitches[i]);
    if (buttonState[i] != lastButtonState[i]) {
      if (buttonState[i] == 0) {
        buttonPushCounter[i]++;
        char count = buttonPushCounter[i];
        Serial.println("on");
        Serial.print("Basylan sany: ");
        Serial.println(buttonPushCounter[i]);
        if(buttonPushCounter[i]==1){
          changeRoomQuery(roomQueries[i],'1');
        }
        if(buttonPushCounter[i]==2){
          changeRoomQuery(roomQueries[i],'2');
        }
        if(buttonPushCounter[i]==3){
          changeRoomQuery(roomQueries[i],'3');
        }
        if(buttonPushCounter[i]==4){
          changeRoomQuery(roomQueries[i],'4');
        }
        if(buttonPushCounter[i]>4){
          buttonPushCounter[i] = 0;
          changeRoomQuery(roomQueries[i],'0');
        }
        Serial.println(roomQueries[i]);
      } else {
        Serial.println("off");
      }
      delay(50);
    }
    lastButtonState[i] = buttonState[i];
  }
}

void changeRoomQuery(int queryIndex,char changingCase){
  char changingQuery;
  int lightIndex;
  if (queryIndex==1){changingQuery = queryRoom1; lightIndex = room1Lights;}
  if (queryIndex==2){changingQuery = queryRoom2; lightIndex = room2Lights;}
  //if (queryIndex==3){changingQuery = queryRoom3; lightIndex = room3Lights;}
  //if (queryIndex==4){changingQuery = queryRoom4; lightIndex = room4Lights;}
  changingQuery = changingCase;

  switch(changingQuery){
    case '1': changeState(lightIndex,state1);break;
    case '2': changeState(lightIndex,state2);break;
    case '3': changeState(lightIndex,state3);break;
    case '4': changeState(lightIndex,state4);break;
    case '0': changeState(lightIndex,allOff);break;
  }
}

void changeState(int lightArray[],int modeArray[]){
  for(int i=0;i<numLights;i++){
    digitalWrite(lightArray[i],modeArray[i]);
  }
}
