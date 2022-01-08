from flask import (
	request,
	make_response,
)
from datetime import datetime
from sqlalchemy import func

from main import app
from main import db

from main.models import (
	Master_device,
	Device,
	Pin,
	Sensor,
	Sensor_record
)
from main.routes_devices import manage_pir_detector_leds


@app.route("/esp/current_measure/")
def current_measure():
	device_key = request.args.get('device_key')
	pin_sensor_command = request.args.get('sensor_command')
	flat_command = request.args.get('flat_command')

	try:
		value = request.args.get('sensor_value')
	except:
		value = None

	print("current measuring+++++++=")
	print(pin_sensor_command, flat_command, value)

	# Device key is current_current_measurer_master
	device = Device.query.filter_by(device_key = device_key).first()
	if device:
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
