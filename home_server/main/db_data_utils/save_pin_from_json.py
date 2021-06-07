
def save_pin_from_json(data):
	return {
		"name": data.get("name"),
		"command": data.get("command"),
		"process_key": data.get("process_key"),
		"secret_key": data.get("secret_key"),
		"description": data.get("description"),
		"action": data.get("action"),
		"deviceId": data.get("deviceId"),
		"dateAdded": data.get("dateAdded"),
		"dateUpdated": data.get("dateUpdated"),
	}