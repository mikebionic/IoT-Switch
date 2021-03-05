schedules = [
	{
		"id": 1,
		"name": "TV on",
		"typeId": 1,
		"deviceId": 22,# to what device it belongs to
		"pinId": 87, #Required pin to use
		"device_command": "tv_remote", #which device to operate
		"pin_action": "tvpower", #what action pin should get
		"description": "Turns tv on when door opens"
	},
	{
		"id": 2,
		"name": "Welcome sound",
		"typeId": 2,
		"deviceId": 22,
		"path": "you-wanna-come-in.wav",
		"description": "Says hello when triggered"
	}
]