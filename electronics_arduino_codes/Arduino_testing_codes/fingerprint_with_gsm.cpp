/*
relay = 4
fingerprintscanner = rx = 8 tx = 7;
led = 13
button = 2
*/
#include <SoftwareSerial.h>
SoftwareSerial SIM900(10, 11);
String textMessage;
String person;
String message;

#include <Adafruit_Fingerprint.h>
int getFingerprintIDez();
SoftwareSerial mySerial(9,10);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
int button = 2;
int led = 13;
int relay = 4;

void setup()  
{
   pinMode(relay,OUTPUT);
   pinMode(led,OUTPUT);
   pinMode(button,INPUT);
   digitalWrite(relay,0);
   digitalWrite(led,0);
  Serial.begin(9600);
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Sensor tapyldy!");
    delay(1000);
     finger.getTemplateCount();
     Serial.print("Sensorda "); Serial.print(finger.templateCount); Serial.println(" barmak yzy yazylan");
     sim_start();
  } else {
    while(true)
    blink();
  }
}
char query = '*';


void loop(){  
  long sec = millis();
  query = '*';
  if(Serial.available()>0){
   query = Serial.read();}
  while(digitalRead(button) == 1){
    open_door();
   if((sec + 5000) < millis()){
     // query = '1';
      break;
   }
   }
   
 switch(query){
  case '1':  Enroll();break;
  case '2':  nowdelete();break;
  case 'D':  deleteF();break;
  default : getFingerprintIDez();break;
 }
  delay(50);     
  query = '*';
}


void open_door(){
  digitalWrite(relay,1);
  delay(1000);    /// rele second 
  digitalWrite(relay,0);
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  {return -1;}
  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  {return -1;}

  if (finger.fingerID==2){Serial.println ("John Doe"); person ="John Doe";}

  if (p == FINGERPRINT_OK) {open_door(); message = person+" Bionika (barlaghana) girdi";
    sendSMS(message);}
  
Serial.print("Tapylan ID #"); Serial.print(finger.fingerID); 
  Serial.print(" takmynan "); Serial.println(finger.confidence);

  return finger.fingerID;
     delay(500); 
}

///////////////////////////////////////////////////////ENROLL////////////////////////////////////////

uint8_t k;
void Enroll(){
  digitalWrite(led,1);
  uint8_t id = 1;
  delay(500);
  id = Findempty();
  k = id;
  while (!getFingerprintEnroll(id));
  digitalWrite(led,0);
}

uint8_t getFingerprintEnroll(uint8_t id) {
  uint8_t p = -1;
  Serial.println("Garasmagynyzy hayys edyan");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Hasaba alyndy");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("barmagy goy");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Komunikasya yalnyslygy");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Surat dogry alynmady");
      Serial.println("217");
      break;
    default:
      Serial.println("Anykdal yalnyslyk");
      Serial.println("217");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Surat konwertirlendi");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Surat dusnuksiz");Serial.println("217");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Komunikasiya yalnyslygy");Serial.println("217");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Barmagyn cyzgylaryny tapmadym");Serial.println("217");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Barmagyn cyzgylaryny tapmadym");Serial.println("217");
      return p;
    default:
      Serial.println("Anykdal yalnyslyk");Serial.println("217");
      return p;
  }
  
  Serial.println("Barmagy ayyr");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }

  p = -1;
  Serial.println("Sol barmagy tazeden goy");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Surata alyndy");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("barmagy goy");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Komunikasiya yalnyslygy");
      Serial.println("217");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Surata almak amala asmady");
      Serial.println("217");
      break;
    default:
      Serial.println("Anykdal yalnyslyk");
      Serial.println("217");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Surat alyndy");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Surat hapa");Serial.println("217");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Komunikasiya yalnyslygy");Serial.println("217");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");Serial.println("217");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");Serial.println("217");
      return p;
    default:
      Serial.println("Unknown error");Serial.println("stop");Serial.println("217");
      return p;
  }
  
  
  // OK converted!
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Barmaklar gabat geldi!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Yalnyslyk");Serial.println("217");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Barmaklar gabat gelmedi");Serial.println("217");
    return p;
  } else {
    Serial.println("Anykdal yalnyshlyk");Serial.println("217");
    return p;
  }   
  
  p = finger.storeModel(k);
  if (p == FINGERPRINT_OK) {
    Serial.println("Yatda sakladym");delay(500);Serial.println(k);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Komunikasiya yalnyslygy");Serial.println("217");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Sol yerde yatda saklap bilmedim");Serial.println("217");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Yazylmak yalnyslygy");Serial.println("217");
    return p;
  } else {
    Serial.println("Anykdal yalnyslyk");Serial.println("217");
    return p;
  }
  
}


uint8_t a = 1;
uint8_t Findempty()
{
while(true){
 uint8_t p = finger.loadModel(a);
  switch (p) {
    case FINGERPRINT_OK:
     
     break;
    
    default:
           return a;
      break;
  }
  a++;}
  return 0;
}


void nowdelete(){
  uint8_t nul = -1;

while(true){
nul = -5;
  Serial.println("Pozmaly elementi yaz :");
  if(Serial.available() > 0){
  nul = Serial.parseInt();
    if(nul > 0){break;}
  }
  delay(300);

}
 
deleteFingerprint(nul);
}


uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;
  
  p = finger.deleteModel(id);

  if (p == FINGERPRINT_OK) {
    Serial.println("Pozuldy!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }   
}

void blink(){
digitalWrite(led,1);
delay(1000);
digitalWrite(led,0);
delay(1000);
}

uint8_t deleteF() {
  uint8_t p = -1;

  for( uint8_t x = 1; x<165;x++){
  p = finger.deleteModel(x);
  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    return p;
  }
  } 
}


void sim_start(){
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(8, LOW);
  delay(3000);
  SIM900.begin(19200);
  delay(20000);
  Serial.print("Çatyldy");
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  SIM900.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);
}

void sendSMS(String message){
  // AT command to set SIM900 to SMS mode
  SIM900.print("AT+CMGF=1\r"); 
  delay(100);
  SIM900.println("AT + CMGS = \"99362377995\""); //send message  //99362377995 Didar
  delay(100);
  SIM900.println(message); 
  delay(100);
 
  SIM900.println((char)26); 
  delay(100);
  SIM900.println();
  delay(5000);  
}
