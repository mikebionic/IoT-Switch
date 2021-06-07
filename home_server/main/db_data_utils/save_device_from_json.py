

def save_device_from_json(data):
	return {
		"name": data.get("name"),
		"ip": data.get("ip"),
		"barcode": data.get("barcode"),
		"device_key": data.get("device_key"),
		"secret_key": data.get("secret_key"),
		"command": data.get("command"),
		"state": data.get("state"),
		"description": data.get("description"),
		"typeId": data.get("typeId"),
		"flatId": data.get("flatId"),
		"roomId": data.get("roomId"),
		"dateAdded": data.get("dateAdded"),
		"dateUpdated": data.get("dateUpdated"),
	}