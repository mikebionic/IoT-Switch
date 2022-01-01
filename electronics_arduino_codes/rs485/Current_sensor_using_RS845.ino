 #include <ModbusMaster.h>

#define MAX485_DE  7
#define MAX485_RE  2

ModbusMaster node;

void preTransmission()
{
  digitalWrite(MAX485_RE, 1);  
  digitalWrite(MAX485_DE, 1);
}

void postTransmission () 
{  
  digitalWrite(MAX485_RE, 0);  
  digitalWrite(MAX485_DE, 0);
}

void setup ()
{
  pinMode(MAX485_RE, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE, 0);  
  digitalWrite(MAX485_DE, 0);

  Serial.begin(115200);

  node.begin(1, Serial);

  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() 
{
  uint8_t resultMain;

  resultMain = node.readInputRegisters(0x3100, 6);
  Serial.println(resultMain);
  Serial.println(node.ku8MBSuccess);
  if (resultMain == node.ku8MBSuccess)
  {
    Serial.println(" - - - - - - - - ");
    Serial.print("Pv Voltage: ");
    Serial.println(node.getResponseBuffer(0x00)/ 100.0f);
    Serial.print("Pv Current: ");
    Serial.println(node.getResponseBuffer(0x01)/ 100.0f);
    Serial.print("Battery Voltage: ");
    Serial.println(node.getResponseBuffer(0x04)/ 100.0f);
    Serial.print("Battery charge current: ");
    Serial.println(node.getResponseBuffer(0x05)/ 100.0f);
  }
  delay(1000);
}
