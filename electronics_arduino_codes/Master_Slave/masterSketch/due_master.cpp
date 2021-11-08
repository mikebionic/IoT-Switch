
int led = 13;
String arduino_process_key = "main_arduino_process_secret_key";
String command = "";
String action = "";
String process_key = "";



// Socketlerin pineri
int sock1pin = 22; // D0
int sock2pin = 23; // D1
int sock3pin = 24; // D2

// aircondinsionerin pinleri
int condmodelow = 25;
int condmodemed = 26;
int condmodehigh = 27;

// PIR sensor
int pirsensorpin = 4;
int pirsensorled = 28;

// Water sensor
int watersensorpin = 5;
int watersensorkl = 29;

// gas sensor
int gassensorpin = 6;

// fire sensor
int firesensorpin = 7;

// gerkon sensor
int gerkonsensorpin = 8;



// take this from devices_config of specific device
String socket_command = "socket";
/////

// take this from devices_config of specific device
String conditioner_command = "conditioner_main";

// device config-dan almaly bu value
String pir_device_command = "pir_sensor";
String water_device_command = "water_sensor_van";
String gas_device_command = "gas_sensor";
String fire_device_command = "fire_command";
String gerkon_device_command = "ping_gerkon";



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
  pinMode(pirsensorpin, INPUT);
  pinMode(pirsensorled, OUTPUT);

  //pir sensor
  pinMode(watersensorpin, INPUT);
  pinMode(watersensorkl, OUTPUT);


  pinMode(gassensorpin, INPUT);
  pinMode(firesensorpin, INPUT);
  pinMode(gerkonsensorpin, INPUT);


}


void send_uart_message(String command, String action) {
  String payload = "command=" + command + "&action=" + action;
//  Serial.println(payload);
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
  if (pirsensorstate == 1) {
    digitalWrite(pirsensorled, 1);
    send_uart_message(pir_device_command, "1");
  }
  else if (pirsensorstate == 0) {
    digitalWrite(pirsensorled, 0);
  }

  //water sensor
  int watersensorstate = digitalRead(watersensorpin);
  if (watersensorstate == 1) {
    digitalWrite(watersensorkl, 1);
    send_uart_message(water_device_command, "1");
  }
  else if (watersensorstate == 0) {
    digitalWrite(watersensorkl, 0);
  }


  int gassensorpinstate = digitalRead(gassensorpin);
  if (gassensorpinstate == 1) {
    send_uart_message(gas_device_command, "1");
  }

  int firesensorpinstate = digitalRead(firesensorpin);
  if (firesensorpinstate == 1) {
    send_uart_message(fire_device_command, "1");
  }

  int gerkonsensorpinstate = digitalRead(gerkonsensorpin);
  if (gerkonsensorpinstate == 1) {
    send_uart_message(gerkon_device_command, "1");
  }

  Serial.print(watersensorstate);
  
  Serial.print(gassensorpinstate);
  
  Serial.print(firesensorpinstate);
  
  Serial.println( gerkonsensorpinstate);



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


  // condinsioner control functions
  //mode_high
  if (command == "mode_low") {
    if (action == "1") {
      digitalWrite(condmodelow, 1);
    }
    else if (action == "0") {
      digitalWrite(condmodelow, 0);
    }
  }

  //mode_med
  if (command == "mode_med") {
    if (action == "1") {
      digitalWrite(condmodemed, 1);
    }
    else if (action == "0") {
      digitalWrite(condmodemed, 0);
    }
  }

  //mode_high
  if (command == "mode_high") {
    if (action == "1") {
      digitalWrite(condmodehigh, 1);
    }
    else if (action == "0") {
      digitalWrite(condmodehigh, 0);
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
