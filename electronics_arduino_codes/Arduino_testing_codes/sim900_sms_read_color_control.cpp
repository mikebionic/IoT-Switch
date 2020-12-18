#include <GSM.h>  
#define PINNUMBER ""  
GSM gsmAccess;  
GSM_SMS sms;  
char senderNumber[20];  
char outGoing[16];  
  
int redPin = 11;  
int greenPin = 10;  
int bluePin = 9;  
String message;  
  
void setup()  
{  
  pinMode(redPin, OUTPUT);  
  pinMode(greenPin, OUTPUT);  
  pinMode(bluePin, OUTPUT);  
  setColour(0, 0, 0); // initialise led to off  
  Serial.begin(9600);  
  while (!Serial) {  
    ;  
  }  
  boolean notConnected = true;  
  
  while (notConnected)  
  {  
    if (gsmAccess.begin(PINNUMBER) == GSM_READY)  
      notConnected = false;  
    else  
    {  
      Serial.println("Not connected");  
      delay(1000);  
    }  
  }  
  
  Serial.println("GSM initialized");  
}  
  
void loop()  
{  
  char c;  
  if (sms.available())  
  {  
    Serial.println("Message received from:");  
    sms.remoteNumber(senderNumber, 20);  
    Serial.println(senderNumber);  
    while (c = sms.read())  
      message += c;   
    Serial.println(message);
    message.toLowerCase(); 
  
    Serial.println("\nEND OF MESSAGE");  

    if (message == "blue")  
    {  
      Serial.println("received message to set BLUE");  
      Serial.println("\nSENDING REPLY");  
      sms.beginSMS(senderNumber);  
      sms.print("SET LED TO BLUE. (Message was blue");  
      sms.endSMS();  
      Serial.println("\nCOMPLETE");  
      setColour(0, 0, 255);  
      message = "";  
    }  
  
    if (message == "green")  
    {  
      Serial.println("received message to set GREEN");  
      Serial.println("\nSENDING REPLY");  
      sms.beginSMS(senderNumber);  
      sms.print("SET LED TO GREEN.");  
      sms.endSMS();  
      Serial.println("\nCOMPLETE");  
      setColour(0, 255, 0);  
      message = "";  
    }  
  
    if (message == "red")  
    {  
      Serial.println("received message to set RED");  
      Serial.println("\nSENDING REPLY");  
      sms.beginSMS(senderNumber);  
      sms.print("SET LED TO RED.");  
      sms.endSMS();  
      Serial.println("\nCOMPLETE");  
      setColour(255, 0, 0);  
      message = "";  
    }  
    sms.flush();  
    Serial.println("MESSAGE DELETED");  
  }  
  delay(1000);  
}

void setColour(int red, int green, int blue)  
{
  analogWrite(redPin, red);  
  analogWrite(greenPin, green);  
  analogWrite(bluePin, blue);  
}