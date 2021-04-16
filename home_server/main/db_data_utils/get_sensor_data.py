from main.models import Sensors


def get_sensor_data():
	sensors = Sensors.query.all()
	data = {
		"sensors": [sensor.json() for sensor in sensors],
		"message": "All sensor datas",
		"type": "sensors"
	}
	return data