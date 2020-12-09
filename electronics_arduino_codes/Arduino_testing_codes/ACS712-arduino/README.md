ACS712 [![Build Status](https://travis-ci.org/rkoptev/ACS712-arduino.svg?branch=master)](https://travis-ci.org/rkoptev/ACS712-arduino)
======
An Arduino library to interact with the ACS712 Hall effect-based linear analog current sensor. Includes DC and RMS AC current measuring. Supports ACS712-05B, ACS712-20A, ACS712-30A sensors. Typical applications include motor control, load detection and management, switch mode power supplies, and overcurrent fault protection.

For more information see the datasheet: http://www.allegromicro.com/~/media/files/datasheets/acs712-datasheet.ashx

The accuracy of the analog sensors in conjunction with the low resolution of built-in Arduino ADC hardly allows you to accurately measure the current. So, this sensor is not suitable for precise measurements, but it will be useful in cases where you need to detect the presence of current and approximately estimate its amount. For more accurate measurements, I recommend using digital sensors such as Adafruit INA219.

Wiring
======
### Arduino
![alt arduino](https://raw.githubusercontent.com/rkoptev/ACS712-arduino/master/img/ACS712_arduino_wiring.jpg)
### ESP8266
In order to use the sensor with the ESP8266, you definitely need to take care of two things:
1. You need a 5V power for the sensor (the ESP works on 3.3V), or you can use Vin pin if you powering board with USB.
2. ESP8266's ADC input works in range 0-1 Volts, it means you need to use voltage divider to convert 0-5V range from sensor to 0-1V (Note that NodeMCU already has built-in voltage divider for 3.3V input, you need to take care about that and add additional resistors or solder wire directly to ESP analog input pin).
![alt esp8266](https://raw.githubusercontent.com/rkoptev/ACS712-arduino/master/img/ACS712_esp8266_wiring.jpg)

Methods
=======
### Constructor:
### **ACS712(** *ACS712_type* type, *uint8_t* _pin **)**
Constructor has two parameters: sensor model and analog input to which it is connected. Supported models: **ACS712_05B**, **ACS712_20A**, **ACS712_30A**

### *float* **getCurrentDC()**
This method reads the value from the current sensor and returns it.

### *float* **getCurrentAC(** *uint16_t* frequency **)**
This method allows you to measure AC voltage. Frequency is measured in Hz. By default frequency is set to 50 Hz. Method use the Root Mean Square technique for the measurement. The measurement itself takes time of one full period (1second / frequency). RMS method allow us to measure complex signals different from the perfect sine wave.

### *int* **calibrate()**
This method reads the current value of the sensor and sets it as a reference point of measurement, and then returns this value. By default, this parameter is equal to half of the maximum value on analog input - 512; however, sometimes this value may vary. It depends on the individual sensor, power issues etc… It is better to execute this method at the beginning of each program. Note that when performing this method, no current must flow through the sensor, and since this is not always possible - there is the following method:

### *void* **setZeroPoint(** *int* _zero **)**
This method sets the obtained value as a zero point for measurements. You can use the previous method once, in order to find out zero point of your sensor and then use this method in your code to set starting point without reading sensor.
