from main.models import Device


def get_device_data(id = None):
	if id:
		devices = Device.query.filter_by(id = id).all()

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