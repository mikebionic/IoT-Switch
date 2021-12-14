#include <Controllino.h>

int led = 13;
String arduino_process_key = "main_arduino_process_secret_key";
String command = "";
String action = "";
String process_key = "";

// DHT sensor setup
#include <DHT.h>
#define DHTPIN CONTROLLINO_D4
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
float hum;
float temp;
float hum2;
float temp2;
long temp_millis = millis();
long temp_millis2 = millis();
long temp_check_delay = 2000;
int setted_temperature = 20;
int setted_humidity = 50;

//DHT - 2;
#define DHT_PIN2 CONTROLLINO_D5
#define DHTTYPE2 DHT22
DHT dht2(DHT_PIN2, DHTTYPE2);

// temp humidity sending codes config
int temp_message_sent = 0;
String temp_device_command = "temp_command";
long temp_message_millis = millis();
String humidity_device_command = "hum_command";
int humidity_message_sent = 0;
long humidity_message_millis = millis();
//////////

// temp humidity sending codes config
int temp_message_sent2 = 0;
String temp_device_command_2 = "temp2_command";
long temp_message_millis2 = millis();
String humidity_device_command_2 = "hum2_command";
int humidity_message_sent2 = 0;
long humidity_message_millis2 = millis();
//////////



// moisture soild command
int soil_message_sent = 0;
String soil_device_command_ = "soil_hum_command";
long soil_message_millis = millis();
String soil_device_command_2 = "soil_hum_command2";
int soil_message_sent2 = 0;
long soil_message_millis2 = millis();
int soil_message_sent3 = 0;
String soil_device_command_3 = "soil_hum_command3";
long soil_message_millis3 = millis();
//////////
// gas config
int gas_message_sent = 0;
String gas_device_command_ = "gas_command";
long gas_message_millis = millis();
//////////

// moisutre sensor
const int dry = 270;
const int pumpPin = CONTROLLINO_R1;
const int soilSensor = CONTROLLINO_A0;
const int soilSensor1 = CONTROLLINO_A1;
const int soilSensor2 = CONTROLLINO_A2;
int moisture = 0;
int moisture1 = 0;
int moisture2 = 0;
long pump_millis = millis();
long pump_watering_delay = 2000;
int pump_on_state = 1;
int pump_off_state = 0;
///////////

// aircondinsionerin pinleri
int condmodelow = CONTROLLINO_D0;
int condmodemed = CONTROLLINO_D1;
int condmodehigh = CONTROLLINO_D2;
int condmodeauto = CONTROLLINO_D3;
// pwm pin of fan
int fanpin = CONTROLLINO_D16;

String conditioner_command = "parnik_conditioner_main";

// 2 mode light control
char room_light = CONTROLLINO_D15;
int roomSwitch = CONTROLLINO_A3;
int buttonState = 0;     // make it 1 if INPUT_PULLUP
int lastButtonState = 0; // make it 1 if INPUT_PULLUP
int buttonPushCounter = 0;

// Greenhouse light control
int lightpin = CONTROLLINO_R2;
String light_device_command = "parnik_light_main";

// Greenhouse socket control
int socketpin = CONTROLLINO_R3;
String socket_device_command = "parnik_socket_main";

// esasy tok cesmesi
int tokpin = CONTROLLINO_R0;

// Gas sensor
int smoke = CONTROLLINO_A4;

// LDR sensor
int ldrpin = CONTROLLINO_A5;



void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);

  dht.begin();
  dht2.begin();
  pinMode(pumpPin, OUTPUT);
  pinMode(soilSensor, INPUT);
  pinMode(soilSensor1, INPUT);
  pinMode(soilSensor2, INPUT);
  digitalWrite(pumpPin, pump_off_state);

  //aircondinsionerin pinleri
  pinMode(condmodelow, OUTPUT);
  pinMode(condmodemed, OUTPUT);
  pinMode(condmodehigh, OUTPUT);
  pinMode(condmodeauto, OUTPUT);
  ////
  pinMode(fanpin, OUTPUT);

  // 2 mode light control button
  pinMode(room_light, OUTPUT); // PWM
  pinMode(roomSwitch, INPUT_PULLUP);
  pinMode(tokpin, OUTPUT);

  // Greenhouse light control
  pinMode(lightpin, OUTPUT);

  // Greenhouse socket control
  pinMode(socketpin, OUTPUT);

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
  moisture1 = analogRead(soilSensor1);
  moisture2 = analogRead(soilSensor2);
  moisture_check();
  temp_check();
  temp_check_2();
  //control_temperature();

  //fotrezistor;
  int fotores = analogRead(ldrpin);
  int delayT = (9. / 550.) * fotores - (9.*200 / 550.) + 1;

  //gas smoke sensor;
  int smokevalue = analogRead(smoke);

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

  if (millis() - temp_message_millis > 5000) {
    temp_message_sent = 0;
  }
  if (millis() - temp_message_millis2 > 5000) {
    temp_message_sent2 = 0;
  }
  if (millis() - soil_message_millis > 5000) {
    soil_message_sent = 0;
  }
  if (millis() - soil_message_millis2 > 5000) {
    soil_message_sent2 = 0;
  }
  if (millis() - soil_message_millis3 > 5000) {
    soil_message_sent3 = 0;
  }
  if (millis() - gas_message_millis > 5000) {
    gas_message_sent = 0;
  }
  if (millis() - humidity_message_millis > 5000) {
    humidity_message_sent = 0;
  }
  if (millis() - humidity_message_millis2 > 5000) {
    humidity_message_sent2 = 0;
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
  // Greenhouse light control
  if (command == "parnik_light") {
    if (action == "1") {
      digitalWrite(lightpin, 1);
    }
    else if (action == "0") {
      digitalWrite(lightpin, 0);
    }
  }

  // Greenhouse socket control
  if (command == "parnik_socket") {
    if (action == "1") {
      digitalWrite(socketpin, 1);
    }
    else if (action == "0") {
      digitalWrite(socketpin, 0);
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
      digitalWrite(condmodelow, 1);
      digitalWrite(condmodemed, 0);
      digitalWrite(condmodehigh, 0);
    }
    else if (action == "0") {
      digitalWrite(condmodelow, 0);
      digitalWrite(condmodemed, 0);
      digitalWrite(condmodehigh, 0);
    }
  }

  //mode_med
  if (command == "mode_med") {
    if (action == "1") {
      digitalWrite(condmodemed, 1);
      digitalWrite(condmodehigh, 0);
      digitalWrite(condmodelow, 1);
     }
    else if (action == "0") {
      digitalWrite(condmodelow, 0);
      digitalWrite(condmodemed, 0);
      digitalWrite(condmodehigh, 0);
    }
  }

  //mode_high
  if (command == "mode_high") {
    if (action == "1") {
      digitalWrite(condmodehigh, 1);
      digitalWrite(condmodemed, 1);
      digitalWrite(condmodelow, 1);
     }
    else if (action == "0") {
      digitalWrite(condmodelow, 0);
      digitalWrite(condmodemed, 0);
      digitalWrite(condmodehigh, 0);
    }
  }
  if (command == "auto_manual_switch") {
    if (action == "auto") {
      digitalWrite(condmodeauto, 1);
     }
    else if (action == "0") {
      digitalWrite(condmodeauto, 0);
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


  if (command == "control_parnik_tok_command") {
    if (action == "1") {
      digitalWrite(tokpin, 1);
    }
    else if (action == "0") {
      digitalWrite(tokpin, 0);
    }
  }

  if (command == "led13") {
    if (action == "on") {
      digitalWrite(led, 1);
    }
    else if (action == "off") {
      digitalWrite(led, 0);
    }
  }
}


void temp_check() {
  if (millis() - temp_millis > temp_check_delay) {
    hum = dht.readHumidity();
    temp = dht.readTemperature();

    // send data to raspberry
    if (temp_message_sent == 0) {
      send_uart_message(temp_device_command, String(temp));
      temp_message_sent = 1;
      temp_message_millis = millis();
    }
    if (humidity_message_sent == 0) {
      send_uart_message(humidity_device_command, String(hum));
      humidity_message_sent = 1;
      humidity_message_millis = millis();
    }

    temp_millis = millis();
  }
}

void temp_check_2() {
  if (millis() - temp_millis2 > temp_check_delay) {
    hum2 = dht2.readHumidity();
    temp2 = dht2.readTemperature();

    // send data to raspberry
    if (temp_message_sent2 == 0) {
      send_uart_message(temp_device_command_2, String(temp2));
      temp_message_sent2 = 1;
      temp_message_millis2 = millis();
    }
    if (humidity_message_sent2 == 0) {
      send_uart_message(humidity_device_command_2, String(hum2));
      humidity_message_sent2 = 1;
      humidity_message_millis2 = millis();
    }

    temp_millis2 = millis();
  }
}


void soil_control() {
  if (soil_message_sent == 0) {
    send_uart_message(soil_device_command_, String(moisture));
    soil_message_sent = 1;
    soil_message_millis = millis();
  }
  if (soil_message_sent2 == 0) {
    send_uart_message(soil_device_command_2, String(moisture1));
    soil_message_sent2 = 1;
    soil_message_millis2 = millis();
  }
  if (soil_message_sent3 == 0) {
    send_uart_message(soil_device_command_3, String(moisture2));
    soil_message_sent3 = 1;
    soil_message_millis3 = millis();
  }

}


void control_temperature() {
  if (temp < setted_temperature) {
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
    if (millis() - pump_millis > pump_watering_delay) {
      digitalWrite(pumpPin, pump_on_state);
    } else {
      digitalWrite(pumpPin, pump_off_state);
    }
  } else {
    pump_millis = millis();
  }
}
