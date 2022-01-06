#define MASTER_EN   8                 // connected to RS485 Enable pin
#define LED 13
String recInput;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(MASTER_EN , OUTPUT);        // Declare Enable pin as output
  Serial.begin(9600);                 // set serial communication baudrate
  digitalWrite(MASTER_EN , LOW);      // Make Enable pin low, Receiving mode ON
}

void loop() {
  if(Serial.available() != 0)
  {
    recInput = Serial.readStringUntil('\n');
//    Serial.print(recInput);
    recInput.trim();

    if (recInput == "Second_sensor")
    {
      digitalWrite( LED , HIGH);    // LED ON
      delay(100);
      digitalWrite( LED , LOW);     // LED OFF
      delay(100);
    }
  }
}
