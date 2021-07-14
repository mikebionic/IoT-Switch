device_types = [
	{
		"device_type_key": 1,
		"name": "ESP-01-binary",
		"description": "ESP8266 Binary data like '/control/1' or '/control/0'"
	},
	{
		"device_type_key": 2,
		"name": "ESP-JSON-to-Arguments",
		"description": "ESP8266 with several arguments provided from data in JSON"
	},
	{
		"device_type_key": 3,
		"name": "Esp8266-command-argument",
		"description": "ESP8266 with argument provided in 'control' from data in 'action' of JSON"
	},
	{
		"device_type_key": 4,
		"name": "Esp8266-Arduino Master communicator",
		"description": "ESP8266 with argument provided 'command' 'action' 'process_key' from data, found in PIN with given 'action' of JSON"
	},
	{
		"device_type_key": 5,
		"name": "ESP camera",
		"description": "Esp camera"
	}
]


sensor_types = [
	{
		"sensor_type_key": 1,
		"name": "Colecting",
		"description": "Values will append the 'value' of a sensor object"
	},
	{
		"sensor_type_key": 2,
		"name": "Rewriting",
		"description": "Values of sensor objects 'value' will be rewritten"
	}
]

triggers = [
	{
		"trigger_key": 1,
		"name": "Colecting",
		"description": "Values will append the 'value' of a sensor object",
		"command": "motion_trigger",
		"state": 0
	}
]