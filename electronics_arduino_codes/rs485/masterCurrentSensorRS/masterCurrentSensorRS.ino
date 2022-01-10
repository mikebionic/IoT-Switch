#define SLAVE_EN  8

const int sensor1 = A0;
const int sensor2 = A1;

int maxPulseCount = 10;
String devicePowerkWh = "0.003"; // maxPulseCount / kW/h!!!!!
int serial_millis_delay = 100;

int flat1_count = 0;
int flat2_count = 0;

int flat1_sensorState = 0;
int flat2_sensorState = 0;

long flat1_millis;
long flat2_millis;

long sensor1_millis;
long sensor2_millis;

String flat1_info = "flat1";
String flat2_info = "flat2";

int flat1_message_sent = 0;
int flat2_message_sent = 0;

void setup() {
  Serial.begin(115200);
  pinMode(SLAVE_EN, OUTPUT);
  digitalWrite(SLAVE_EN, 0);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
}

void loop() {
  flat1_sensorState = analogRead(sensor1);
  flat2_sensorState = analogRead(sensor2);

 if (millis() - sensor1_millis > 150){
    if (flat1_sensorState >= 10){
      flat1_count++;
      sensor1_millis = millis();
    }
  }
 
  if (millis() - sensor2_millis > 150){
    if (flat2_sensorState >= 10){
      flat2_count++;
      sensor2_millis = millis();
    }
  }

  check_count_and_send();
}

void check_count_and_send(){
  if (flat1_count >= maxPulseCount){
    if (flat1_message_sent == 0){
      flat1_message_sent = 1;
      flat1_count = 0;
    }
  } else {
    flat1_millis = millis();
  }

 // // // DELAYYYYYYYYYYYYYYYYYYYYY
  if (flat1_count >= maxPulseCount){
      digitalWrite(SLAVE_EN , 1);
      delay(5);
      Serial.println("flat_key=" + flat1_info+"&sensor_value="+devicePowerkWh);
      flat1_count = 0;
      delay(100);
      digitalWrite(SLAVE_EN , 0);
     }
  
  // // // DELAYYYYYYYYYYYYYYYYYYYYY
  if (flat2_count >= maxPulseCount){
      digitalWrite(SLAVE_EN , 1);
      delay(5);
      Serial.println("flat_key=" + flat2_info+"&sensor_value="+devicePowerkWh);
      flat2_count = 0;
      delay(100);
      digitalWrite(SLAVE_EN , 0);
     }
  
    
  Serial.print("Flat1:");
  Serial.println(flat1_count);
  Serial.print("Flat2:");
  Serial.println(flat2_count);
}
