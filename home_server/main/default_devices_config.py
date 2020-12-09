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


sensor_types = [
	{
		"id": 1,
		"name": "Colecting",
		"description": "Values will append the 'value' of a sensor object"
	},
	{
		"id": 2,
		"name": "Rewriting",
		"description": "Values of sensor objects 'value' will be rewritten"
	}
]