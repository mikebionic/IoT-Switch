const int  buttonPin = 2;    
const int ledPin2 = 13;      
const int ledPin1 = 9;

int counter = 0;  
int buttonState = 0;        
int lastButtonState = 0;     
void setup() {
 
  pinMode(buttonPin, INPUT_PULLUP);
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
 
  Serial.begin(9600);
}
void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == 0) {
      counter++;
    }
    delay(50);
  }
  lastButtonState = buttonState;
  if (counter > 0) {
    digitalWrite(ledPin1, 1);
  }
  if (counter >= 2 ) {
    digitalWrite(ledPin2, 1);
  }
  if (counter >= 3){
    counter = 0;
  }
  else if (counter == 0){
    digitalWrite(ledPin2, 0);
    digitalWrite(ledPin1, 0);
  }
}
