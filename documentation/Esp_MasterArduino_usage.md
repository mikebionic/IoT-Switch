# Device TypeId = 4


| route                             | method |
| --------------------------------- | ------ |
| http://<server_ip>/esp/JsonToArg/ | POST   |

So you create a device like following:
```json
{
	"id": 99999,
	"name": "ESP of master arduino",
	"ip": "192.168.1.253",
	"device_key": "ESP_ARDU_MASTER",
	"command": "esp_communicator_secret",
	"typeId": 4,
	"description": "Communicates with master arduino via UART"
}
```
**command** is the secret key, which is used to select the needed esp device, to send request to

As a good example, I will show how to make control of conditioner Pin.
You should add Pins to control the registered arduino pins like following:
```json
{
	"name": "Arduino Conditioner Mode HIGH",
	"command": "mode_high",
	"description": "Changes the conditioner operation power",
	"action": "0",
	"process_key": "main_arduino_process_secret_key",
	"deviceId": 99999,
}
```

**deviceId** is the ID of device it belongs to. In our example this will be the **"ESP of master arduino"**
We also could program the Conditioner to accept the "mode" parameter, and send action "high" or "low", then your json will change to:

```json
{
	"name": "Arduino Conditioner Mode",
	"command": "mode",
	"description": "Changes the conditioner operation power",
	"action": "low",
	"process_key": "main_arduino_process_secret_key",
	"deviceId": 99999,
}
```

---

## How to operate this device and pins of device typeId = 4

Example request json for that device:
```json
{
	"command": "esp_communicator_secret",
	"pins": [
		{
			"command": "mode_high",
			"action": "1"
		}
	]
}
```

It will send to Master Arduino's Esp the request, that will look like:

```url
http://192.168.1.253/control/?command=mode_high&action=1&process_key=main_arduino_process_secret_key
```
**192.168.1.253** is the remote ESP's IP address that we configured in **Device Config** json.

The **process_key** is the arduino's secret key, which is used to specify the microprocessor that should work on this command, and it adds security for IoT system. In our case it is **main_arduino_process_secret_key**

---

[Esp communicator sketch](../electronics_arduino_codes/Master_Slave/masterEsp.cpp)
[Master arduino sketch](../electronics_arduino_codes/Master_Slave/masterSketch/masterSketch_v25.ino)
