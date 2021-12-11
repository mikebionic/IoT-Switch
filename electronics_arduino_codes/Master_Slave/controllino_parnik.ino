#include <Controllino.h>

int led = 13;
String arduino_process_key = "main_parnik_process_secret_key";
String command = "";
String action = "";
String process_key = "";

// DHT sensor setup
#include <DHT.h>
#define DHTPIN CONTROLLINO_A4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float hum;
float temp;
long temp_millis = millis();
long temp_check_delay = 2000;
int setted_temperature = 20;
int setted_humidity = 50;

// temp humidity sending codes config 
int temp_message_sent = 0;
String temp_device_command = "parnik_temp_sensor";
long temp_message_millis = millis();
String humidity_device_command = "parnik_humidity_sensor";
int humidity_message_sent = 0;
long humidity_message_millis = millis();
//////////

// moisutre sensor
const int dry = 270;
const int pumpPin = CONTROLLINO_R12;
const int soilSensor = CONTROLLINO_A5;
int moisture = 0;
long pump_millis = millis();
long pump_watering_delay = 2000;
int pump_on_state = 1;
int pump_off_state = 0;
///////////

// aircondinsionerin pinleri
int condmodelow = CONTROLLINO_R13;
int condmodemed = CONTROLLINO_R14;
int condmodehigh = CONTROLLINO_R15;
// pwm pin of fan
int fanpin = CONTROLLINO_D0;

String conditioner_command = "parnik_conditioner_main";

// 2 mode light control
char room_light = CONTROLLINO_D1;
int roomSwitch = CONTROLLINO_A7;
int buttonState = 0;     // make it 1 if INPUT_PULLUP
int lastButtonState = 0; // make it 1 if INPUT_PULLUP
int buttonPushCounter = 0;

// esasy tok cesmesi
int tokpin = CONTROLLINO_R8;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);

  dht.begin();
  pinMode(pumpPin, OUTPUT);
  pinMode(soilSensor, INPUT);
  digitalWrite(pumpPin, pump_off_state);

  //aircondinsionerin pinleri
  pinMode(condmodelow, OUTPUT);
  pinMode(condmodemed, OUTPUT);
  pinMode(condmodehigh, OUTPUT);
  ////
  pinMode(fanpin, OUTPUT);

  // 2 mode light control button
  pinMode(room_light, OUTPUT); // PWM
  pinMode(roomSwitch, INPUT_PULLUP);
  pinMode(tokpin, OUTPUT);
}


void send_uart_message(String command, String action) {
  String payload = "command=" + command + "&action=" + action;
  Serial.println(payload);
}


void loop() {

  if (Serial.available() != 0) {
    String stream = Serial.readStringUntil('\n');
    stream.trim();
    if (stream.length() > 0) {
      command = getStringPartByDelimeter(stream, ':', 0);
      action = getStringPartByDelimeter(stream, ':', 1);
      process_key = getStringPartByDelimeter(stream, ':', 2);

      if (process_key == arduino_process_key) {
        control_device(command, action);
      }

    }
  }

  // moisture sensor
  moisture = analogRead(soilSensor);
  moisture_check();
  temp_check();
  control_temperature();

  // 2 mode ring lignt control button
  buttonState = digitalRead(roomSwitch);
  if (buttonState != lastButtonState) {
    if (buttonState == 1) { // change 1 to 0 if INPUT_PULLUP
      buttonPushCounter++;
      char count = buttonPushCounter;
      if (buttonPushCounter == 1) {
        digitalWrite(room_light, 1);
      }
      if (buttonPushCounter > 1) {
        buttonPushCounter = 0;
        digitalWrite(room_light, 0);
      }
    }
    delay(50);
  }
  lastButtonState = buttonState;

  if (millis() - temp_message_millis > 5000){
    temp_message_sent = 0;
  }
}


String getStringPartByDelimeter(String data, char separator, int index) {
  int stringData = 0;
  String dataPart = "";
  for (int i = 0; i < data.length() - 1; i++) {
    if (data[i] == separator) {
      stringData++;
    } else if (stringData == index) {
      dataPart.concat(data[i]);
    } else if (stringData > index) {
      return dataPart;
      break;
    }
  }
  return dataPart;
}


void control_device(String command, String action) {

  // room light
  if (command == "parnik_room_light") {
    if (action == "1") {
      digitalWrite(room_light, 1);
    }
    else if (action == "0") {
      digitalWrite(room_light, 0);
    }
  }

  // setting temperature
  if (command == "parnik_temp_set") {
    setted_temperature = action.toInt();
  }
  // setting humidity
  if (command == "parnik_humidity_set") {
    setted_humidity = action.toInt();
  }


  // condinsioner control functions
  //mode_high
  if (command == "mode_low") {
    if (action == "1") {
      analogWrite(fanpin, 10);
      digitalWrite(condmodelow, 1);
      digitalWrite(condmodemed, 0);
      digitalWrite(condmodehigh, 0);
    }
    else if (action == "0") {
      digitalWrite(condmodelow, 0);
    }
  }

  //mode_med
  if (command == "mode_med") {
    if (action == "1") {
      analogWrite(fanpin, 50);
      digitalWrite(condmodemed, 1);
      digitalWrite(condmodehigh, 0);
      digitalWrite(condmodelow, 0);
    }
    else if (action == "0") {
      digitalWrite(condmodemed, 0);
    }
  }

  //mode_high
  if (command == "mode_high") {
    if (action == "1") {
      analogWrite(fanpin, 255);
      digitalWrite(condmodehigh, 1);
      digitalWrite(condmodemed, 0);
      digitalWrite(condmodelow, 0);
    }
    else if (action == "0") {
      digitalWrite(condmodehigh, 0);
    }
  }
  if (command == "auto_manual_switch") {
    if (action == "auto") {
      analogWrite(fanpin, 0);
      digitalWrite(condmodehigh, 0);

    }
    else if (action == "0") {
      digitalWrite(condmodehigh, 0);
    }
  }

  if (command == "parnik_water_pump") {
    if (action == "1") {
      digitalWrite(pumpPin, 1);
    }
    else if (action == "0") {
      digitalWrite(pumpPin, 0);
    }
  }
  

  if (command == "control_tok_command") {
    if (action == "1") {
      digitalWrite(tokpin, 1);
    }
    else if (action == "0") {
      digitalWrite(tokpin, 0);
    }
  }

  if(command == "led13") {
    if (action == "on") {
      digitalWrite(led, 1);
    }
    else if (action == "off") {
      digitalWrite(led, 0);
    }
  }
}


void temp_check() {
  if (millis() - temp_millis > temp_check_delay){
    hum = dht.readHumidity();
    temp = dht.readTemperature();

    // send data to raspberry
    if (temp_message_sent == 0){
      send_uart_message(temp_device_command, String(temp));
      temp_message_sent = 1;
      temp_message_millis = millis();
    }
    if (humidity_message_sent == 0){
      send_uart_message(humidity_device_command, String(hum));
      humidity_message_sent = 1;
      humidity_message_millis = millis();
    }

    temp_millis = millis();
  }
}

void control_temperature() {
  if (temp < setted_temperature){
    analogWrite(fanpin, 255);
    digitalWrite(condmodehigh, 1);
    digitalWrite(condmodemed, 0);
    digitalWrite(condmodelow, 0);
  } else {
    analogWrite(fanpin, 0);
    digitalWrite(condmodehigh, 0);
    digitalWrite(condmodemed, 0);
    digitalWrite(condmodelow, 0);
  }
}


void moisture_check() {
  if (moisture >= dry) {
    if (millis() - pump_millis > pump_watering_delay){ 
      digitalWrite(pumpPin, pump_on_state);
    } else {
      digitalWrite(pumpPin, pump_off_state);
    }
  } else {
    pump_millis = millis();
  }
}