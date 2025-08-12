# Smart Home ESP Controllers Registration and Control Project

**Latest production-ready version:** 09/2020 – 06/2022
**Deployment:** Smart Home automation system in *"16-njy Tapgyr"* and *"Gorjaw"* residential areas.

![Smart Home System](https://mikebionic.github.io/portfolio/static/projects/using/Smart_house_oguzhan.webp)

---

## Overview

A complete Smart Home automation platform built on ESP8266 microcontrollers and an ARM-based Linux server.
The system supports local and remote control, integrates with multiple IoT devices, and features security, monitoring, and automated comfort adjustments.

**Core features:**

* MQTT-like device communication between IoT modules and a Raspberry Pi server.
* Automatic local network mode when connected to home Wi-Fi; internet-based remote control when away.
* Flexible device integration — from lights and curtains to heaters, ovens, and security systems.
* Multi-layer security with fingerprint, RFID, and motion detection.

---

## Used Components

* ESP8266 ESP-01 Microcontrollers
* Microcomputer (ARM Linux, e.g., Raspberry Pi)
* Wi-Fi router
* Relays
* 3.3V → 5V converter
* Power adapter & voltage stabilizer for ESP modules
* SIM900 GSM module (for SMS alerts)
* Various sensors: PIR, water leak, gas, temperature, current, and flow measurement.
* **And yes — a bit of patience.**

---

## Devices & Systems in the Project

* [x] Lights & light bulbs
* [x] Heater & cooler
* [x] Stove (SIEMENS stove reverse-engineered)
* [x] Curtains
* [x] TV remote control
* [x] Smart sockets & window control
* [x] Water pump control (with water sensor)
* [x] Current & water flow measurement
* [x] CCTV security
* [x] Fingerprint access control (built-in & wireless)
* [x] RFID/NFC card access control
* [x] SIM900 SMS control option
* [x] PIR security sensors
* [x] Face recognition service

---

## Security Features

* Entrance doors equipped with RFID and fingerprint sensors.
* Automatic logging of entry events with timestamp and captured photo.
* Motion detection with failed-attempt recognition.
* Instant alerts to the mobile app and via SMS for:

  * Unauthorized access
  * Fire, gas, or water leak detection
* Backup power for continued operation during power outages.

---

## Example Device Integrations

* **Kitchen devices control** — [Video](https://youtu.be/GPi_x9mvyAw?feature=shared) | ![Cooker](https://mikebionic.github.io/portfolio/static/projects/using/cooker.webp)
* **Curtain control** — [Video](https://youtu.be/nL0T0GI-RSc?feature=shared) | ![Curtains](https://mikebionic.github.io/portfolio/static/projects/using/curtain.webp)
* **Lights control** — [Video](https://youtu.be/Sv5fxklOzlo?feature=shared) | ![Lights](https://mikebionic.github.io/portfolio/static/projects/using/lights_control.webp)

---

## Documentation

* [Server Side (EN)](/documentation/server-side_enUS.md)
* [Server Side (RU)](/documentation/server-side_ruRU.md)
* [Server Side (TM)](/documentation/server-side_tkTM.md)
* [Smart Home (EN)](/documentation/smart-home_enUS.md)
* [Smart Home (RU)](/documentation/smart-home_ruRU.md)
* [Smart Home (TM)](/documentation/smart-home_tkTM.md)

---

## ESP8266 Pinouts & Hardware References

**ESP8266-01**
![ESP8266-01](datasheet/esp8266-01.png)

**NodeMCU ESP8266**
![NodeMCU](datasheet/NodeMCUesp8266.png)

**A4988 Stepper Driver**
![A4988](datasheet/A4988.jpg)

**Adafruit Fingerprint Sensor**
![Fingerprint Sensor](datasheet/fingerprint-sensor-pinout.jpg)

---

## API Testing Examples

**POST control command**

```bash
curl --header "Content-Type: application/json" \
     --request POST \
     --data '{"command":"test_local","state":1,"action":""}' \
     http://127.0.0.1:5000/esp/
```

**POST JSON to arguments**

```bash
curl --header "Content-Type: application/json" \
     --request POST \
     --data '{"command":"test_local_json","pins":[{"command":"switch_mirror","action":"1"},{"command":"switch_AI","action":"activate"}]}' \
     http://127.0.0.1:5000/esp/JsonToArg/
```

**Browser GET example**

```
http://192.168.1.252/esp/ArgToDB/?device_key=<device_key>&command=<sensor_command>&value=<value>
```

---

## PIR Sensor Workflow

**From Controllino to Raspberry Pi:**

```
http://192.168.1.252:5000/esp/ArgToDB/?command=pir_sensor&device_key=ESP_ARDU_MASTER&isMaster=1&action=0
```

(`action` changes depending on sensor state)

**Trigger PIR mode:**

```bash
curl --header "Content-Type: application/json" \
     --request POST \
     --data '{"command":"pir_led_selector_command","state":1,"action":""}' \
     http://192.168.1.252:5000/esp/JsonToArg/
```


## Mobile App Screenshots

| | | |
|---|---|---|
| <img src="https://mikebionic.github.io/portfolio/static/projects/smart_home_screens/smart_home_app_screens11.webp" width="200"/> | <img src="https://mikebionic.github.io/portfolio/static/projects/smart_home_screens/smart_home_app_screens5.webp" width="200"/> | <img src="https://mikebionic.github.io/portfolio/static/projects/smart_home_screens/smart_home_app_screens3.webp" width="200"/> |
| <img src="https://mikebionic.github.io/portfolio/static/projects/smart_home_screens/smart_home_app_screens6.webp" width="200"/> | <img src="https://mikebionic.github.io/portfolio/static/projects/smart_home_screens/smart_home_app_screens9.webp" width="200"/> | <img src="https://mikebionic.github.io/portfolio/static/projects/smart_home_screens/smart_home_app_screens10.webp" width="200"/> |
| <img src="https://mikebionic.github.io/portfolio/static/projects/smart_home_screens/smart_home_app_screens1.webp" width="200"/> | <img src="https://mikebionic.github.io/portfolio/static/projects/smart_home_screens/smart_home_app_screens2.webp" width="200"/> | <img src="https://mikebionic.github.io/portfolio/static/projects/smart_home_screens/smart_home_app_screens5.webp" width="200"/> |

