from flask import (
	request,
	make_response,
)
from datetime import datetime
from sqlalchemy import func

from main import app
from main import db

from main.models import (
	Flat,
	Sensor,
	Sensor_record
)


@app.route("/get_flat_sensors/")
def get_flat_sensors():
	flat_key = request.args.get('flat_key')

	# ## This feature already written somewhere
	
	# try:
	# 	this_flat = Flat.query.filter_by(secret_key = flat_key).first()
	# 	if not this_flat:
	# 		raise Exception

	# 	# sensor_records = 






	# Device key is used to secure a little bit from hacking as a master arduino
	try:
		value = request.args.get('sensor_value')
	except:
		value = None

	print("current measuring+++++++=")
	print(current_sensor_command, flat_key, value)

	try:
		# Device key is current_get_flat_sensorsr_master
		device = None
		if isMaster:
			device = Master_device.query.filter_by(device_key = device_key).first()
		else:
			device = Device.query.filter_by(device_key = device_key).first()
		if not device:
			print("device not found or not registered")
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
					flatId = sensor.flatId
					sensorId = sensor.id
				)\
				.filter(
					func.date(Sensor_record.date) == current_date
				).first()

			if found_s_record:
				found_s_record.value += value

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
		return make_response("err",200)
