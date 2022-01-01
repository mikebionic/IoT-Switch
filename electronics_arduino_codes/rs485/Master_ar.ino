#define MASTER_EN   8                 // connected to RS485 Enable pin
#define SWITCH      6                 // Declare LED pin
 
void setup() {
  pinMode(SWITCH , INPUT_PULLUP);     // Declare LED pin as output
  pinMode(MASTER_EN , OUTPUT);        // Declare Enable pin as output
  Serial.begin(9600);                 // set serial communication baudrate 
  digitalWrite(MASTER_EN , LOW);      // Make Enable pin low, Receiving mode ON
}
 
void loop() {
  if(digitalRead(SWITCH) == 0)
  {                      // Debouncing for switch
    digitalWrite(MASTER_EN , HIGH);     // Make Enable pin high to send Data
    delay(5);                           // required minimum delay of 5ms
    Serial.println("EMBEDDED GATE");     // Send String serially, End String with *
    delay(5);
//    Serial.flush();                     // wait for transmission of data
    digitalWrite(MASTER_EN , LOW);      // Receiving mode ON
  }
}
