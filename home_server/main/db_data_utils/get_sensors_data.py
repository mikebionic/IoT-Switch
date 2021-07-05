from main.models import Sensor, Sensor_record


def get_sensors_data(
	id = None,
	db_models = None,
	with_records = False,
):

	if id:
		sensors = Sensor.query.filter_by(id = id).all()

	elif db_models:
		sensors = db_models

	else:
		sensors = Sensor.query.all()
	
	data = []
	for sensor in sensors:
		info = sensor.json()
		if with_records:
			records = Sensor_record.query\
				.filter_by(sensorId = sensor.id).all()
			info["sensor_records"] = [record.json() for record in records]
		data.append(info)

	res = {
		"data": data,
		"message": "All sensor datas",
		"type": "sensors"
	}
	return res