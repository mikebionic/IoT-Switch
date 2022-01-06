#define SLAVE_EN  8
const int button1 = A0;
const int button2 = A1;
const int ledPin =  13;
int firstbuttonState = 0;// Variable to store Receive string
int secondbuttonState = 0;// Variable to store Receive string

void setup() {
  pinMode(ledPin, OUTPUT);                        // Declare LED pin as output
  pinMode(SLAVE_EN, OUTPUT);                   // Declare Enable pin as output
  pinMode(button1, INPUT);
  Serial.begin(9600);                           // set serial communication baudrate
  digitalWrite(SLAVE_EN, LOW);               // Make Enable pin low, Receiving mode ON
}

void loop() {
  firstbuttonState = analogRead(button1);
  if (firstbuttonState >= 10)
  {
    digitalWrite(SLAVE_EN , HIGH);
    delay(5);
    Serial.println("First_sensor");
    delay(100);
    //    Serial.flush();
    digitalWrite(SLAVE_EN , LOW);
  }
  secondbuttonState = analogRead(button2);
  if (secondbuttonState >= 10)
  {
    digitalWrite(SLAVE_EN , HIGH);
    delay(5);
    Serial.println("Second_sensor");
    delay(100);
    //    Serial.flush();
    digitalWrite(SLAVE_EN , LOW);
  }
}
