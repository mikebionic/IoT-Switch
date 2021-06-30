from main.models import Sensor


def get_sensor_data():
	sensors = Sensor.query.all()
	data = {
		"sensors": [sensor.json() for sensor in sensors],
		"message": "All sensor datas",
		"type": "sensors"
	}
	return data