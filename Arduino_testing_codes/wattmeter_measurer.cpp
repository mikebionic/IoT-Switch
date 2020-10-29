#include "ACS712.h"
int count = 0;
int interval = 60;
int myArray [60];
int myArray2 [60];
double sumP = 0;
double sumP2 = 0;

ACS712 sensor(ACS712_30A, A0);
ACS712 sensor2(ACS712_30A, A1);
void setup() {
  Serial.begin(9600);
  sensor.calibrate();
  sensor2.calibrate();
}

void loop() {
  float U = 230;
  float I = sensor.getCurrentAC();
  float I2 = sensor2.getCurrentAC();
  if (I >= 0.06 && I <= 0.1) I = 0;
  if (I2 >= 0.06 && I2 <= 0.1) I2 = 0;
  float P = U * I;
  float P2 = U * I2;
  Serial.println(P);
  Serial.println(P2);
  count += 1;
  myArray[count -1] = P;
  myArray2[count -1] = P2;
  if (count == interval)
  {
    for (int i = 0; i <= interval-1; i++)
    {
      sumP += myArray[i];
      sumP2 += myArray2[i];
    }
    Serial.println(String("P = ") + sumP + " Watts");
    Serial.println(String("P = ") + sumP2 + " Watts");    
    count = 0;
    sumP = 0;
    sumP2 = 0;
  }
  delay(1000);
}
