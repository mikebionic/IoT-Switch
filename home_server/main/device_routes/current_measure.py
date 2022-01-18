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
	Flat,
	Pin,
	Sensor,
	Sensor_record
)
from main.routes_devices import manage_pir_detector_leds


# http://127.0.0.1:5000/esp/current_measure/?flat_key=flat1_secret_key_hash&sensor_value=13

@app.route("/esp/current_measure/")
def current_measure():
	device_key = request.args.get('device_key', "", str)
	current_sensor_command = "current_measurer"#request.args.get('sensor_command')
	flat_key = request.args.get('flat_key')
	isMaster = request.args.get('isMaster', 0, int)

	# Device key is used to secure a little bit from hacking as a master arduino
	try:
		value = request.args.get('sensor_value')
	except:
		value = None

	print("current measuring+++++++=")
	print(current_sensor_command, flat_key, value)

	try:
		# # Device key is current_current_measurer_master
		# # This feature is not important, could be added for security
		# device = None
		# if isMaster:
		# 	device = Master_device.query.filter_by(device_key = device_key).first()
		# else:
		# 	device = Device.query.filter_by(device_key = device_key).first()
		# if not device:
		# 	print("device not found or not registered")
		# 	raise Exception

		this_flat = Flat.query.filter_by(secret_key = flat_key).first()
		if not this_flat:
			raise Exception

		value = float(value)
		# sensor should contain flatID
		sensor = Sensor.query\
			.filter_by(flatId = this_flat.id, command = current_sensor_command)\
			.first()
		if not sensor:
			print("no sensor found")
			raise Exception

		if sensor.typeId == 1:
			sensor.value += value

			current_date = datetime.now().date()
			found_s_record = Sensor_record.query\
				.filter_by(
					flatId = sensor.flatId,
					sensorId = sensor.id
				)\
				.filter(
					func.date(Sensor_record.date) == current_date
				).first()

			if found_s_record:
				found_s_record.value += value
				found_s_record.dateUpdated = datetime.now()

			else:
				sensor_record_payload = {
					"deviceId": sensor.deviceId,
					"sensorId": sensor.id,
					"flatId": sensor.flatId,
					"value": value,
					"date": current_date
				}

				new_record = Sensor_record(**sensor_record_payload)
				db.session.add(new_record)
				db.session.commit()

			
		elif sensor.typeId == 2:
			sensor.value = float(value)
		db.session.commit()
		return make_response("ok",200)

	except Exception as ex:
		print("Current meaure exception", ex)
		return make_response("err",200)
