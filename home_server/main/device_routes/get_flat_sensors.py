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
	try:
		this_flat = Flat.query.filter_by(secret_key = flat_key).first()
		if not this_flat:
			raise Exception

		# sensor should contain flatID
		sensor = Sensor.query\
			.filter_by(flatId = this_flat.id, command = current_sensor_command)\
			.first()
		if not sensor:
			print("no sensor found")
			raise Exception

		data = sensor.json()
		data["sensor_records"] = [record.json() for record in sensor.sensor_records]
		return data

	except Exception as ex:
		return make_response("err",200)
