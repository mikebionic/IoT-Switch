byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin1      = 2;
byte sensorInterrupt2 = 0;
byte sensorPin2      = 4;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;

volatile byte pulseCount;  
volatile byte pulseCount2;  

float flowRate;
float flowRate2;

unsigned int flowMilliLitres;
unsigned int flowMilliLitres2;
unsigned long totalMilliLitres;
unsigned long totalMilliLitres2;

unsigned long oldTime;
unsigned long pTime = 30000;
unsigned long oldTime2 = 0;


void setup(){
  Serial.begin(9600);
  pinMode(sensorPin1, INPUT);
  digitalWrite(sensorPin1, 1);
  pinMode(sensorPin2, INPUT);
  digitalWrite(sensorPin2, 1);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;

  pulseCount2        = 0;
  flowRate2          = 0.0;
  flowMilliLitres2   = 0;
  totalMilliLitres2  = 0;
  oldTime           = 0;
  
}


void loop(){
  measureAndSend();
}


void measureAndSend() {
  if(millis() - oldTime2 >= 5000)
  {
    int value = totalMilliLitres/1000*2;
    int value2 = totalMilliLitres2/1000*2;
    unsigned int total_value = value + value2;
    String value_water = String(total_value);
    Serial.println(value);
    Serial.println(value2);
    Serial.println(total_value);
     
    oldTime2 = millis();
    totalMilliLitres = 0;
    value_water = "";
    totalMilliLitres2 = 0;
  }
  if((millis() - oldTime) > 1000)    // Only process counters once per second
  {
    detachInterrupt(sensorInterrupt);
    detachInterrupt(sensorInterrupt2);

    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    flowRate2 = ((1000.0 / (millis() - oldTime)) * pulseCount2) / calibrationFactor;

    oldTime = millis();

    flowMilliLitres = (flowRate / 60) * 1000;
    flowMilliLitres2 = (flowRate2 / 60) * 1000;
    
    totalMilliLitres += flowMilliLitres;
    totalMilliLitres2 += flowMilliLitres2;
      
    unsigned int frac;
    
    pulseCount = 0;
    pulseCount2 = 0;
    
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    attachInterrupt(sensorInterrupt2, pulseCounter, FALLING);
  }
}


void pulseCounter()
{
  pulseCount++;
  pulseCount2++;
}
