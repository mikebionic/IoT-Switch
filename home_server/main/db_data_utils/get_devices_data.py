from sqlalchemy.orm import joinedload
from main.models import Device


def get_devices_data(id = None, db_models = None):
	if id:
		devices = Device.query\
			.filter_by(id = id)\
			.options(
				joinedload(Device.sensors),
				joinedload(Device.pins),
			)\
			.all()

	elif db_models:
		devices = db_models

	else:
		devices = Device.query\
			.options(
				joinedload(Device.sensors),
				joinedload(Device.pins),
			)\
			.all()

	data = []
	for device in devices:
		info = device.json()
		pins = [pin.json() for pin in device.pins]
		info['pins'] = pins
		sensors = [sensor.json() for sensor in device.sensors]
		info['sensors'] = sensors
		data.append(info)


	res = {
		"data": data,
		"message": "All sensor datas",
		"type": "sensors"
	}
	return res