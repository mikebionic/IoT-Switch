#include <Controllino.h>

int led = 13;
String arduino_process_key = "main_arduino_process_secret_key";
String command = "";
String action = "";
String process_key = "";

// curtain sketch
long curtain_delay = 2000; // seconds of curtain spin
long curtain_time = millis();
long curtainTime;
int curtain_up_button = CONTROLLINO_A0;
int curtain_down_button = CONTROLLINO_A1;
int curtain_direction = 0; // curtain up if = 1, down if = 2

// curtain dc motor
int curtain_up_motor = CONTROLLINO_R0;
int curtain_down_motor = CONTROLLINO_R1;



// Socketlerin pineri
int sock1pin = CONTROLLINO_R2; // D0
int sock2pin = CONTROLLINO_R3; // D1
int sock3pin = CONTROLLINO_R4; // D2

// PIR sensor
int pirsensorpin = CONTROLLINO_A2;
int pirsensorled = CONTROLLINO_R5;

// Water sensor
int watersensorpin = CONTROLLINO_A3;
int suwklapanpin = CONTROLLINO_R12;

// aircondinsionerin pinleri
int condmodelow = CONTROLLINO_R13;
int condmodemed = CONTROLLINO_R14;
int condmodehigh = CONTROLLINO_R15;


// gas sensor
int gassensorpin = CONTROLLINO_A4;

// fire sensor
int firesensorpin = CONTROLLINO_A5;

// gerkon sensor
int gerkonsensorpin = CONTROLLINO_A6;

// pwm pin of fan
int fanpin = CONTROLLINO_D0;

// take this from devices_config of specific device
// device config-dan almaly bu value
String socket_command = "socket";
String conditioner_command = "conditioner_main";
String pir_device_command = "pir_sensor";
String water_device_command = "water_sensor_van";
String gas_device_command = "gas_sensor";
String fire_device_command = "fire_command";
String gerkon_device_command = "ping_gerkon";
String curtain_device_command = "curtain";
String kitchen_light_device_command = "kitchen_light123";
String control_tok_device_command = "control_tok_command";
String water_pump_device_command = "suw_klapan";

// 4 MODE DIMMER
char room_light = CONTROLLINO_D1;
int roomSwitch = CONTROLLINO_A7;
int buttonState = 0;     // make it 1 if INPUT_PULLUP
int lastButtonState = 0; // make it 1 if INPUT_PULLUP
int buttonPushCounter = 0;

// Kitchen light
int kitchenlightpin = CONTROLLINO_R7;

// esasy tok cesmesi
int tokpin = CONTROLLINO_R8;


int fire_message_sent = 0;
int pir_message_sent = 0;
long pir_message_millis;
int water_message_sent = 0;
int gas_message_sent = 0;
int gerkon_message_sent = 0;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);

  //socketlerin pinleri
  pinMode(sock1pin, OUTPUT);
  pinMode(sock2pin, OUTPUT);
  pinMode(sock3pin, OUTPUT);
  ////

  //aircondinsionerin pinleri
  pinMode(condmodelow, OUTPUT);
  pinMode(condmodemed, OUTPUT);
  pinMode(condmodehigh, OUTPUT);
  ////

  //pir sensor
  pinMode(pirsensorpin, INPUT_PULLUP);
  pinMode(pirsensorled, OUTPUT);

  //pir sensor
  pinMode(watersensorpin, INPUT_PULLUP);
  pinMode(suwklapanpin, OUTPUT);

  pinMode(gassensorpin, INPUT_PULLUP);
  pinMode(firesensorpin, INPUT_PULLUP);
  pinMode(gerkonsensorpin, INPUT_PULLUP);

  pinMode(fanpin, OUTPUT);

  // 4 MODE DIMMER
  pinMode(room_light, OUTPUT); // PWM
  pinMode(roomSwitch, INPUT_PULLUP);

  // curtain sketch
  pinMode(curtain_up_button, INPUT_PULLUP);
  pinMode(curtain_down_button, INPUT_PULLUP);

  pinMode(curtain_up_motor, OUTPUT);
  pinMode(curtain_down_motor, OUTPUT);

  pinMode(kitchenlightpin, OUTPUT);

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
  //pir sensor
  int pirsensorstate = digitalRead(pirsensorpin);
  if (millis() - pir_message_millis > 5000){
    pir_message_sent = 0;
  }
  if (pirsensorstate == 1) {
    if (pir_message_sent == 0){
//      digitalWrite(pirsensorled, 1);
      send_uart_message(pir_device_command, "1");
      pir_message_sent = 1;
      pir_message_millis = millis();
    }
  }
  else if (pirsensorstate == 0) {
      if (pir_message_sent == 0){
    //    digitalWrite(pirsensorled, 0);
        send_uart_message(pir_device_command, "0");  
        pir_message_sent = 1;
        pir_message_millis = millis();
      }
  }

  //water sensor
  int watersensorstate = digitalRead(watersensorpin);
  if (watersensorstate == 1) {
    if (water_message_sent == 0){
      digitalWrite(suwklapanpin, 1);
      send_uart_message(water_device_command, "1");
      water_message_sent = 1;
    }
  }
  else if (watersensorstate == 0) {
    digitalWrite(suwklapanpin, 0);
    water_message_sent = 0;
  }


  int gassensorpinstate = digitalRead(gassensorpin);
  if (gassensorpinstate == 1) {
    if (gas_message_sent == 0){
      send_uart_message(gas_device_command, "1");
      gas_message_sent = 1;    
    }
  } else {
    gas_message_sent = 0;
  }

  int firesensorpinstate = digitalRead(firesensorpin);
  if (firesensorpinstate == 1) {
    if (fire_message_sent == 0){
      send_uart_message(fire_device_command, "1"); 
      fire_message_sent = 1;
    }
  } else {
    fire_message_sent = 0;
  }

  int gerkonsensorpinstate = digitalRead(gerkonsensorpin);
  if (gerkonsensorpinstate == 1) {
    if (gerkon_message_sent == 0){
      send_uart_message(gerkon_device_command, "1");
      gerkon_message_sent = 1;    
    }
  } else {
    gerkon_message_sent = 0;
  }


  // 4 mode Dimmer
  buttonState = digitalRead(roomSwitch);
  if (buttonState != lastButtonState) {
    if (buttonState == 1) { // change 1 to 0 if INPUT_PULLUP
      buttonPushCounter++;
      char count = buttonPushCounter;
      if (buttonPushCounter == 1) {
        analogWrite(room_light, 10);
      }
      if (buttonPushCounter == 2) {
        analogWrite(room_light, 100);
      }
      if (buttonPushCounter == 3) {
        analogWrite(room_light, 255);
      }
      if (buttonPushCounter > 3) {
        buttonPushCounter = 0;
        analogWrite(room_light, 0);
      }
    }
    delay(50);
  }
  lastButtonState = buttonState;


  // curtain setup buttons
  int curtain_up_button_state = digitalRead(curtain_up_button);
  int curtain_down_button_state = digitalRead(curtain_down_button);

  if (curtain_up_button_state == 1) {
    curtainTime = millis();
    curtain_direction = 1;
  }

  if (curtain_down_button_state == 1) {
    curtainTime = millis();
    curtain_direction = 2;
  }

  if (curtainTime + curtain_delay > millis()) {
    if (curtain_direction == 1) {
      digitalWrite(curtain_up_motor, 1);
      digitalWrite(curtain_down_motor, 0);
    }
    if (curtain_direction == 2) {
      digitalWrite(curtain_down_motor, 1);
      digitalWrite(curtain_up_motor, 0);
    }
  } else {
    digitalWrite(curtain_up_motor, 0);
    digitalWrite(curtain_down_motor, 0);
  }
  //////////

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

  // socket control functions
  if (command == "socket1") {
    if (action == "1") {
      digitalWrite(sock1pin, 1);
    }
    else if (action == "0") {
      digitalWrite(sock1pin, 0);
    }
  }
  else if (command == "socket2") {
    if (action == "1") {
      digitalWrite(sock2pin, 1);
    }
    else if (action == "0") {
      digitalWrite(sock2pin, 0);
    }
  }
  else if (command == "socket3") {
    if (action == "1") {
      digitalWrite(sock3pin, 1);
    }
    else if (action == "0") {
      digitalWrite(sock3pin, 0);
    }

    else if (action == "uartoff") {
      send_uart_message("0", socket_command);
    }
  }
  //////

  // kitchen light
  if (command == "kitchen_light123") {
    if (action == "1") {
      digitalWrite(kitchenlightpin, 1);
    }
    else if (action == "0") {
      digitalWrite(kitchenlightpin, 0);
    }
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

 if (command == "suw_klapan") {
    if (action == "1") {
      digitalWrite(suwklapanpin, 1);
    }
    else if (action == "0") {
      digitalWrite(suwklapanpin, 0);
    }
  }
    
  // Myhman otag led pwm
  if (command == "three_mode_switch") {
    if (action == "1") {
      analogWrite(room_light, 10);
    }
    else if (action == "2") {
      analogWrite(room_light, 100);
    }
    else if (action == "3") {
      analogWrite(room_light, 255);
    }
    else if (action == "0") {
      analogWrite(room_light, 0);
    }
  }

  //curtain dc motor
  if (command == "curtain") {
    if (action == "1") {
      digitalWrite(curtain_up_motor, 1);
      digitalWrite(curtain_down_motor, 0);
      delay(1000);
    }
    else if (action == "2") {
      digitalWrite(curtain_up_motor, 0);
      digitalWrite(curtain_down_motor, 1);
      delay(1000);
    }
    else if (action == "0") {
      digitalWrite(curtain_up_motor, 0);
      digitalWrite(curtain_down_motor, 0);
    }
  }

    if (command == "pir_led_command") {
        if (action == "1") {
        digitalWrite(pirsensorled, 1);
        }
        else if (action == "0") {
        digitalWrite(pirsensorled, 0);
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
