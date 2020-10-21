devices = [
	{
		"name": "Lights Hall",
		"ip": "192.168.1.145",
		"state": 0,
		"device_key": "dfj7sdf40dg",
		"typeId": 1,
		"command": "lights_hall",
		"description": "Turns on/off hall lights"
	},
	{
		"name": "Lights Kitchen",
		"ip": "192.168.1.101",
		"state": 0,
		"device_key": "a45bcKewefEfd",
		"typeId": 1,
		"command": "lights_kitchen",
		"description": "Turns on/off kitchen lights"
	},
	{
		"name": "Lights Main Room",
		"ip": "192.168.1.102",
		"state": 0,
		"device_key": "24t346g5y88732Efd",
		"typeId": 1,
		"command": "lights_main",
		"description": "Turns on/off Main Room lights"
	},
	{
		"name": "Lights Bedroom",
		"ip": "192.168.1.211",
		"state": 0,
		"device_key": "abcKey88732Efd",
		"typeId": 1,
		"command": "lights_bedroom",
		"description": "Turns on/off bedroom lights"
	},
	{
		"name": "Lights Bedroom2",
		"ip": "192.168.1.212",
		"state": 0,
		"device_key": "a4i827i3732E45",
		"typeId": 1,
		"command": "lights_bedroom2",
		"description": "Turns on/off bedroom2 lights"
	},
	{
		"name": "Lights Bedroom3",
		"ip": "192.168.1.213",
		"state": 0,
		"device_key": "MHD57odcio732Efd",
		"typeId": 1,
		"command": "lights_bedroom3",
		"description": "Turns on/off bedroom3 lights"
	},
	{
		"name": "Lights Bedroom4",
		"ip": "192.168.1.214",
		"state": 0,
		"device_key": "fvh6a23rbef28732r",
		"typeId": 1,
		"command": "lights_bedroom4",
		"description": "Turns on/off bedroom4 lights"
	},
	{
		"name": "Lights Add",
		"ip": "192.168.1.215",
		"state": 0,
		"device_key": "mdc03knb8873i3m",
		"typeId": 1,
		"command": "lights_add",
		"description": "Turns on/off Added lights"
	},
	{
		"name": "Curtain",
		"ip": "192.168.1.123",
		"state": 0,
		"device_key": "sqs20n7nI9mdio2mew",
		"typeId": 1,
		"command": "curtain",
		"description": "Moves up and down the curtain"
	},
	{
		"name": "Smart conditioner",
		"ip": "192.168.1.243",
		"state": 0,
		"device_key": "conD9mdc73om934",
		"typeId": 3,
		"command": "conditioner",
		"description": "Controls conditioner"
	},
	{
		"name": "Local test",
		"ip": "127.0.0.1:5000",
		"state": 0,
		"device_key": "23abcK238873244",
		"typeId": 1,
		"command": "test_local",
		"description": "Turns on/off Local test"
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
		"name": "ESP-01-command",
		"description": "ESP8266 with argument provided in 'control'"
	},
	{
		"id": 3,
		"name": "NodeMCU-command",
		"description": "ESP8266 with argument provided in 'control'"
	}
]