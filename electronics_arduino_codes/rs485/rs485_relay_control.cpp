
int enable = 6;
int transmit = 1;
int receive = 0;

byte devId = 0x01;
byte ON_RELAY_1[8] = {devId, 0x05,0x00,0x00,0xFF,0x00,0x8C,0x3A};
byte OFF_RELAY_1[8] = {devId, 0x05,0x00,0x00,0x00,0x00,0xCD,0xCA};

byte ON_RELAY_2[8] = {devId, 0x05,0x00,0x01,0xFF,0x00,0xDD,0xFA};
byte OFF_RELAY_2[8] = {devId, 0x05,0x00,0x01,0x00,0x00,0x5C,0x0A};

byte ON_RELAY_3[8] = {devId, 0x05,0x00,0x02,0xFF,0x00,0x2D,0xFA};
byte OFF_RELAY_3[8] = {devId, 0x05,0x00,0x02,0x00,0x00,0x6C,0x0A};

byte ON_RELAY_4[8] = {devId, 0x05,0x00,0x03,0xFF,0x00,0x7C,0x3A};
byte OFF_RELAY_4[8] = {devId, 0x05,0x00,0x03,0x00,0x00,0x3D,0xCA};

void setup(){
    pinMode(enable, OUTPUT);
    digitalWrite(enable, receive);
    Serial.begin(9600);
}

void loop(){
    digitalWrite(enable, transmit);
    Serial.write(ON_RELAY_1,8);
    delay(500);
    Serial.write(OFF_RELAY_1,8);
    delay(500);
    Serial.write(ON_RELAY_2,8);
    delay(500);
    Serial.write(OFF_RELAY_2,8);
    delay(500);
    Serial.write(ON_RELAY_3,8);
    delay(500);
    Serial.write(OFF_RELAY_3,8);
    delay(500);
    Serial.write(ON_RELAY_4,8);
    delay(500);
    Serial.write(OFF_RELAY_4,8);
    delay(500);
}
