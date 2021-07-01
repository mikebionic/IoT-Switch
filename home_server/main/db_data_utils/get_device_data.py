from main.models import Device


def get_device_data(id = None, device_models = None):
	if id:
		devices = Device.query.filter_by(id = id).all()

	elif device_models:
		devices = device_models

	else:
		devices = Device.query.all()

	data = []
	for device in devices:
		info = device.json()
		pins = [pin.json() for pin in device.pins]
		info['pins'] = pins
		sensors = [sensor.json() for sensor in device.sensors]
		info['sensors'] = sensors
		data.append(info)
	return data