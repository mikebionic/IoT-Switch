// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3

#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance
unsigned long previousMillis = 0;
void setup()
{     
  Serial.begin(115200);
  
  emon1.current(1, 17.15);             // Current: input pin, calibration.
}

void loop()
{
  unsigned long currentMillis = millis();
  double Irms = emon1.calcIrms(1480);  // Calculate Irms only
  if(currentMillis - previousMillis >= 1000)
  {
    previousMillis = currentMillis;
    if(Irms >= 0.1)
    {
        Serial.println(Irms*220.0);         // Apparent power
    }
    else
    {
      Irms = 0;
    }
  }
		       // Irms
}
