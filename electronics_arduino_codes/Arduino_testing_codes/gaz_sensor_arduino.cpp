int signal_pin = 2;
int status_led = 13;
int reset_pin = 5;
int trigger_pin = 7;
long off_time;

void setup() {
  Serial.begin(9600);
  pinMode(signal_pin, INPUT);
  pinMode(status_led, OUTPUT);
  pinMode(reset_pin, OUTPUT);
  pinMode(trigger_pin, INPUT_PULLUP);
  digitalWrite(status_led, 0);
  digitalWrite(reset_pin, 0);
}

void loop(){
  int signal_state = digitalRead(signal_pin);
  int trigger_state = digitalRead(trigger_pin);
  check_signal_state(signal_state);
  if (trigger_state == 0){
    call_reset();
  }
}

void check_signal_state(int signal_state){
  if (signal_state == 1){
    digitalWrite(status_led, 1);
    off_time = millis();
  }
  else {
    Serial.println(off_time);
    if (off_time + 2000 < millis()){
      Serial.println("it is finally off");
    }
    digitalWrite(status_led, 0);
  }
}

void call_reset(){
  Serial.println("reset called");
  digitalWrite(reset_pin, 1);
  delay(100);
  digitalWrite(reset_pin, 0);
}