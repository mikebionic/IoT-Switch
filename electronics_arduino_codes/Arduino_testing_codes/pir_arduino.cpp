int pir_sensor = 8;
int led = 13;

void setup(){
	pinMode(led, OUTPUT);
	pinMode(pir_sensor, INPUT);
	digitalWrite(led, 0);
}

void loop(){
	int pir_value = digitalRead(pir_sensor);
	if (pir_value == 1){
		digitalWrite(led, 1);
	}
	else if (pir_value == 0){
		digitalWrite(led, 0);
	}
}