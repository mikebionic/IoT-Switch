# Smart Home Esp controllers registration and control project

Used components:

+ ESP8266 ESP-01 Microcontrollers
+ Microcomputer running ARM linux
+ Wifi router
+ Relay
+ 3.3v to 5v converter
+ Power adapter and stabilizator for esp microcontroller
+ Patience

---------------

ESP-01 devices have two active pins - Led output (GPIO 2) and Switch (GPIO 0)

Connect those pins in a correctly by schematics and record ESP's ip-address.
Add ip address to a database of python server app.
Send JSON command to a linux server and let him execute the rest thing.

---------------

# Compile and run the ESP8266 microprocessor code

> check ip addresses to be used
> check devices and device commands

**Esp8266-01** pinout
![ESP8266-01](datasheet/esp8266-01.png)

**NodeMCU-Esp8266** pinout
![NodeMCU](datasheet/NodeMCUesp8266.png)


**A4988 Stepper driver** pinout
![A4988](datasheet/A4988.jpg)