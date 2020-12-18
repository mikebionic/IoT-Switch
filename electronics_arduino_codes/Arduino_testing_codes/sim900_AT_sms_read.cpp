#include <dht.h>
#define dhtdat 10
dht DHT;
#include <SoftwareSerial.h>
SoftwareSerial SIM900(2, 3);
String inMessage;
String lamp1State = "Ocuk";
String lamp2State = "Ocuk";
String lamp3State = "Ocuk";
String dhtState = "";

const int lamp1 = 4;
const int lamp2 = 5;
const int lamp3 = 6;
int lamp1_St = 0;
int lamp2_St = 0;
int lamp3_St = 0;
String stateMessage;

long x=millis();

void setup() {
  pinMode(lamp1, OUTPUT);
  pinMode(lamp2, OUTPUT);
  pinMode(lamp3, OUTPUT);
  digitalWrite(lamp1, 0);
  digitalWrite(lamp2, 0);
  digitalWrite(lamp3, 0);
  sim_start();

}
void loop(){
  temp_status();
  
  if(SIM900.available()>0){
    inMessage = SIM900.readString();
    Serial.print(inMessage);    
    delay(10);
  }
  if(inMessage.indexOf("Cyra a yak")>=0){
    lamp1_St=1;
    relay();
  }
  if(inMessage.indexOf("Cyra a ocur")>=0){
      lamp1_St=0;
    relay();
  }
    if(inMessage.indexOf("Cyra b yak")>=0){
    lamp2_St=1;
    relay(); 
  }
  if(inMessage.indexOf("Cyra b ocur")>=0){
      lamp2_St=0;
    relay();
  }
    if(inMessage.indexOf("Cyra c yak")>=0){
    lamp3_St=1;
    relay(); 
  }
  if(inMessage.indexOf("Cyra c ocur")>=0){
      lamp3_St=0;
    relay();
  }
  if(inMessage.indexOf("Yagday")>=0){
   state();
  }
  
}  

void relay(){
    digitalWrite(lamp1,lamp1_St);
    digitalWrite(lamp2,lamp2_St);
    digitalWrite(lamp3,lamp3_St);

    if (lamp1_St==1){
      lamp1State = "Yanyar"; 
      Serial.println("Rele yandy");
    }
    if (lamp1_St==0){
      lamp1State = "Ocuk"; 
      Serial.println("Rele ocdi");
    }
    if (lamp2_St==1){
      lamp2State = "Yanyar"; 
      Serial.println("Rele yandy");
    }
    if (lamp2_St==0){
      lamp2State = "Ocuk"; 
      Serial.println("Rele ocdi");
    }
    if (lamp3_St==1){
      lamp3State = "Yanyar"; 
      Serial.println("Rele yandy");
    }
    if (lamp3_St==0){
      lamp3State = "Ocuk"; 
      Serial.println("Rele ocdi");
    }    
    inMessage = ""; 
}

void state(){
   String lamp_1 = "Cyra1 " + lamp1State;
   String lamp_2 = "Cyra2 " + lamp2State;
   String lamp_3 = "Cyra3 " + lamp3State;
    Serial.println("Yagdayy sorayar");
    //stateMessage=lamp_1+lamp_2+lamp_3; //??? MAYBE
    sendSMS(stateMessage);
    inMessage = "";
}

void sendSMS(String stateMessage){
  SIM900.print("AT+CMGF=1\r");
  delay(100);
  SIM900.println("AT + CMGS = \"99365123456\"");
  delay(100);
  SIM900.println(stateMessage+dhtState); 
  delay(100);
 
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  delay(5000);  
}

void temp_status(){
  if ((x+4000)<millis()){ 
    float readData = DHT.read11(dhtdat);
    unsigned int t=DHT.temperature;
    unsigned int h=DHT.humidity;
    String tmp= "Temp = " + t;
    String hum="Cyglylyk = "+h;
    dhtState = tmp+hum;
    //dhtState = ("Temp = ", + t, +" *C ",+"Cyglylyk ",+h,+" %");
    x=millis();
  }
}

void sim_start(){
  digitalWrite(7, HIGH);
  delay(1000);
  digitalWrite(8, LOW);
  delay(3000);
  SIM900.begin(19200);
  delay(15000);
  Serial.print("Chatyldy");
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}