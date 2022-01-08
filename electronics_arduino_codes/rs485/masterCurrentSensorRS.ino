#define SLAVE_EN  8

const int sensor1 = A0;
const int sensor2 = A1;

int maxPulseCount = 10;
int devicePowerkWh = 3000;
int serial_millis_delay = 100;

int flat1_count = 0;
int flat2_count = 0;

int flat1_sensorState = 0;
int flat2_sensorState = 0;

long flat1_millis;
long flat2_millis;

String flat1_info = "flat1";
String flat2_info = "flat2";

int flat1_message_sent = 0;
int flat2_message_sent = 0;

void setup() {
  Serial.begin(9600);
  pinMode(SLAVE_EN, OUTPUT);
  digitalWrite(SLAVE_EN, 0);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
}

void loop() {
  flat1_sensorState = analogRead(sensor1);
  flat2_sensorState = analogRead(sensor2);

  if (flat1_sensorState >= 10){flat1_count++;}
  if (flat2_sensorState >= 10){flat2_count++;
  Serial.println(flat2_count);}

  check_count_and_send();
}

void check_count_and_send(){
  if (flat1_count >= maxPulseCount){
    if (flat1_message_sent == 0){
      // serial_send_power_info(flat1_info, flat1_count * devicePowerkWh, flat1_millis, flat1_count, flat1_message_sent);
      flat1_message_sent = 1;
      flat1_count = 0;
    }
  } else {
    flat1_millis = millis();
  }


  ///////////
  ////// millis
  // if (flat2_count >= maxPulseCount){
  //   if (flat2_message_sent == 0){
  //     // serial_send_power_info(flat2_info, flat2_count * devicePowerkWh, flat2_millis, flat2_count, flat2_message_sent);
  //     digitalWrite(SLAVE_EN , 1);
  //     Serial.println("111111111 ============= " + millis() - flat2_millis);
  //     if (millis() - flat2_millis > 5){
  //       Serial.println("!!!!!!!!!!!!!!!" + flat2_info+":"+flat2_count * devicePowerkWh+":");
  //       if (millis() - flat2_millis > 100){
  //         digitalWrite(SLAVE_EN , 0);
  //         flat2_count = 0;
  //         flat2_message_sent = 1;
  //       }
  //     }
  //   }
  // } else {
  //   flat2_millis = millis();
  //   flat2_message_sent = 0;
  // }
  ///////////
 
  // // // DELAYYYYYYYYYYYYYYYYYYYYY
  if (flat2_count >= maxPulseCount){
    // if (flat2_message_sent == 0){
      digitalWrite(SLAVE_EN , 1);
      Serial.println("111111111 ============= " + millis() - flat2_millis);
      delay(5);
      Serial.println("!!!!!!!!!!!!!!!" + flat2_info+":"+flat2_count * devicePowerkWh+":");
      flat2_count = 0;
      // flat2_message_sent = 1;
      delay(100);
      digitalWrite(SLAVE_EN , 0);
    // }
  }
  // /////////////
  
  Serial.println(flat2_count);
  Serial.println(flat2_message_sent);
  Serial.println(flat2_millis);
}

// void serial_send_power_info(String flatInfo, int value, long flat_millis, int flat_count, int flat_message_sent){
//   digitalWrite(SLAVE_EN , 1);
//   if (millis() - flat_millis > 5){
//     Serial.println(flatInfo+":"+value+":");
//     if (millis() - flat_millis > 100){
//       digitalWrite(SLAVE_EN , 0);
//       flat2_count = 0;
//       flat2_message_sent = 1;
//     }
//   }
// }