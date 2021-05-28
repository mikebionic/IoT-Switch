from flask import (
	request,
	make_response,
)

from main import app
from main import db

from main.models import (
	Devices,
	Pins,
	Sensors,
)


@app.route("/esp/ArgToDB/",methods=['GET'])
def esp_arg_to_db():
	device_key = request.args.get('device_key')
	pin_sensor_command = request.args.get('command')

	try:
		value = request.args.get('value')
	except:
		value = None

	try:
		action = request.args.get('action')
	except:
		action = None

	device = Devices.query.filter_by(device_key = device_key).first()
	if device:
		if action:
			try:
				pin = Pins.query\
					.filter_by(deviceId = device.id, command = pin_sensor_command)\
					.first()

				if pin:
					pin.action = action
					db.session.commit()
					# print(device.name)
					return make_response("ok",200)
				return make_response("not Found",200)
			except Exception as ex:
				print(ex)
				return make_response("err",200)

		if value:
			try:
				sensor = Sensors.query\
				.filter_by(deviceId = device.id, command = pin_sensor_command)\
				.first()
				if sensor:
					if sensor.typeId == 1:
						sensor.value += float(value)
					elif sensor.typeId == 2:
						sensor.value = float(value)
					db.session.commit()
					# print(device.name)
					return make_response("ok",200)
				return make_response("not Found",200)
			except Exception as ex:
				return make_response("err",200)
