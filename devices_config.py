devices = [
	{
		"id": 1,
		"name": "Lights Hall",
		"ip": "192.168.1.145",
		"state": 0,
		"device_key": "dfj7sdf40dg",
		"typeId": 1,
		"command": "lights_hall",
		"description": "Turns on/off hall lights"
	},
	{
		"id": 2,
		"name": "Lights Kitchen",
		"ip": "192.168.1.101",
		"state": 0,
		"device_key": "a45bcKewefEfd",
		"typeId": 1,
		"command": "lights_kitchen",
		"description": "Turns on/off kitchen lights"
	},
	{
		"id": 3,
		"name": "Lights Main Room",
		"ip": "192.168.1.102",
		"state": 0,
		"device_key": "24t346g5y88732Efd",
		"typeId": 1,
		"command": "lights_main",
		"description": "Turns on/off Main Room lights"
	},
	{
		"id": 4,
		"name": "Lights Bedroom",
		"ip": "192.168.1.211",
		"state": 0,
		"device_key": "abcKey88732Efd",
		"typeId": 1,
		"command": "lights_bedroom",
		"description": "Turns on/off bedroom lights"
	},
	{
		"id": 5,
		"name": "Lights Bedroom2",
		"ip": "192.168.1.212",
		"state": 0,
		"device_key": "a4i827i3732E45",
		"typeId": 1,
		"command": "lights_bedroom2",
		"description": "Turns on/off bedroom2 lights"
	},
	{
		"id": 6,
		"name": "Lights Bedroom3",
		"ip": "192.168.1.213",
		"state": 0,
		"device_key": "MHD57odcio732Efd",
		"typeId": 1,
		"command": "lights_bedroom3",
		"description": "Turns on/off bedroom3 lights"
	},
	{
		"id": 7,
		"name": "Lights Bedroom4",
		"ip": "192.168.1.215",
		"state": 0,
		"device_key": "mdc03knb8873i3m",
		"typeId": 1,
		"command": "lights_bedroom4",
		"description": "Turns on/off bedroom4 lights"
	},
	{
		"id": 8,
		"name": "Curtain",
		"ip": "192.168.1.123",
		"state": 0,
		"device_key": "sqs20n7nI9mdio2mew",
		"typeId": 1,
		"command": "curtain",
		"description": "Moves up and down the curtain"
	},
	{
		"id": 9,
		"name": "Smart conditioner",
		"ip": "192.168.1.243",
		"state": 0,
		"device_key": "conD9mdc73om934",
		"typeId": 2,
		"command": "conditioner",
		"description": "Controls conditioner"
	},
	{
		"id": 10,
		"name": "ESP-01 Smart Socket",
		"ip": "192.168.1.144",
		"state": 0,
		"device_key": "knb78G^n03foi",
		"typeId": 2,
		"command": "socket",
		"description": "Controls Smart socket"
	},
	{
		"name": "Local binary test",
		"ip": "127.0.0.1:5000",
		"state": 0,
		"device_key": "23abcK238873244",
		"typeId": 1,
		"command": "test_local",
		"description": "Turns on/off Local test"
	},
	{
		"id": 999,
		"name": "Local Json to Args test",
		"ip": "127.0.0.1:5000",
		"state": 0,
		"device_key": "ase44f3f23f3",
		"typeId": 2,
		"command": "test_local_json",
		"description": "Json to args of local test func"
	}
]

pins = [
	{
		"id": 1,
		"name": "Socket1",
		"command": "socket1",
		"description": "Pin 2 of smart socket",
		"action": "0",
		"deviceId": 10,
	},
	{
		"id": 2,
		"name": "Socket2",
		"command": "socket2",
		"description": "Pin 2 of smart socket",
		"action": "0",
		"deviceId": 10,
	},
	{
		"id": 3,
		"name": "Socket3",
		"command": "socket3",
		"description": "Pin3 of smart socket",
		"action": "0",
		"deviceId": 10,
	},
	{
		"id": 4,
		"name": "Conditioner Mode HIGH",
		"command": "mode_high",
		"description": "Changes the conditioner operation power",
		"action": "0",
		"deviceId": 9,
	},
	{
		"id": 5,
		"name": "Conditioner Mode MED",
		"command": "mode_med",
		"description": "Changes the conditioner operation power",
		"action": "0",
		"deviceId": 9,
	},
	{
		"id": 6,
		"name": "Conditioner Mode LOW",
		"command": "mode_low",
		"description": "Changes the conditioner operation power",
		"action": "0",
		"deviceId": 9,
	},
	{
		"id": 7,
		"name": "Conditioner Auto/Manual switch",
		"command": "auto_manual_switch",
		"description": "Changes the use of manual or auto mode (Tel mode)",
		"action": "auto",
		"deviceId": 9,
	},
	{
		"id": 8,
		"name": "Temperature control",
		"command": "temperature",
		"description": "Controls room temperature according to command (ex.: 'heater:25:' or 'cooler:16:')",
		"action": "cooler:20:",
		"deviceId": 9,
	},
	{
		"id": 998,
		"name": "Mirror switch",
		"command": "switch_mirror",
		"description": "Mirror actuator pin",
		"action": "0",
		"deviceId": 999,
	},
	{
		"id": 999,
		"name": "AI pin",
		"command": "switch_AI",
		"description": "Activates AI function",
		"action": "0",
		"deviceId": 999,
	}
]

device_types = [
	{
		"id": 1,
		"name": "ESP-01-binary",
		"description": "ESP8266 Binary data like '/control/1' or '/control/0'"
	},
	{
		"id": 2,
		"name": "ESP-JSON-to-Arguments",
		"description": "ESP8266 with several arguments provided from data in JSON"
	},
	{
		"id": 3,
		"name": "Esp8266-command-argument",
		"description": "ESP8266 with argument provided in 'control' from data in 'action' of JSON"
	}
]