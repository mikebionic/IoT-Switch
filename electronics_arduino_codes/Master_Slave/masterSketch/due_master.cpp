
int led = 13;
String arduino_process_key = "main_arduino_process_secret_key";
String command = "";
String action = "";
String process_key = "";



// Socketlerin pineri
int sock2pin = 4; // D0
int sock1pin = 5; // D1
int sock3pin = 6; // D2
/////


void setup() {
  Serial.begin(115200);
  pinMode(led,OUTPUT);

  //socketlerin pinleri
  pinMode(sock1pin, OUTPUT);
  pinMode(sock2pin, OUTPUT);
  pinMode(sock3pin, OUTPUT);
  ////
}

void loop() {
  if(Serial.available() != 0){
    String stream = Serial.readStringUntil('\n');
    stream.trim();
    if (stream.length()>0){
      command = getStringPartByDelimeter(stream,':',0);
      action = getStringPartByDelimeter(stream,':',1);
      process_key = getStringPartByDelimeter(stream,':',2);

      if (process_key == arduino_process_key){
        control_device(command, action);
      }

    }
  }
}


String getStringPartByDelimeter(String data, char separator, int index){
  int stringData = 0;
  String dataPart = "";
  for(int i = 0; i<data.length()-1; i++){
    if(data[i]==separator) {
      stringData++;
    }else if(stringData==index) {
      dataPart.concat(data[i]);
    }else if(stringData>index){
      return dataPart;
      break;
    }
  }
  return dataPart;
}


void control_device(String command, String action){

  // socket control functions
  if (command == "socket1") {
    if(action == "1"){
        digitalWrite(sock1pin,1);
    }
    else if(action == "0"){
        digitalWrite(sock1pin,0);
    }
  }
  else if (command == "socket2"){
    if(action == "1"){
        digitalWrite(sock2pin,1);
    }
    else if(action == "0"){
        digitalWrite(sock2pin,0);
    }
  }
  else if (command == "socket3"){
    if(action == "1"){
        digitalWrite(sock3pin,1);
    }
    else if(action == "0"){
        digitalWrite(sock3pin,0);
    }
  }
  //////




  if (command == "led13"){
    if (action == "on"){
      digitalWrite(led, 1);
    }
    else if (action == "off"){
      digitalWrite(led, 0);
    }
  }
}