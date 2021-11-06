from flask import (
	request,
	make_response,
)
from datetime import datetime
from sqlalchemy import func

from main import app
from main import db

from main.models import (
	Device,
	Pin,
	Sensor,
	Sensor_record
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

	device = Device.query.filter_by(device_key = device_key).first()
	if device:
		if action:
			try:
				pin = Pin.query\
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
			value = float(value)
			try:
				sensor = Sensor.query\
				.filter_by(deviceId = device.id, command = pin_sensor_command)\
				.first()
				if sensor:
					if sensor.typeId == 1:
						sensor.value += value

						current_date = datetime.now().date()
						found_s_record = Sensor_record.query\
							.filter_by(
								deviceId = device.id,
								sensorId = sensor.id
							)\
							.filter(
								func.date(Sensor_record.date) == current_date
							).first()

						if found_s_record:
							found_s_record.value += value

						else:
							sensor_record_payload = {
								"deviceId": device.id,
								"sensorId": sensor.id,
								"value": value,
								"date": current_date
							}

							new_record = Sensor_record(**sensor_record_payload)
							db.session.add(new_record)
							db.session.commit()

						
					elif sensor.typeId == 2:
						sensor.value = float(value)
					db.session.commit()
					# print(device.name)
					return make_response("ok",200)
				return make_response("not Found",200)
			except Exception as ex:
				return make_response("err",200)
