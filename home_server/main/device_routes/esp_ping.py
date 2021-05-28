from flask import (
	request,
	make_response,
)

from main import app
from main import db

from main.models import (
	Devices,
)

# record esp's ip address to db
@app.route("/esp/ping/")
def esp_ping():
	device_key = request.args.get('device_key')
	ip_address = request.args.get('ip_address')
	# command = request.args.get('command')
	device = Devices.query.filter_by(device_key = device_key).first()
	if device:
		try:
			device.ip = ip_address
			db.session.commit()
		except Exception as ex:
			print(ex)
			return make_response("err", 200)
		return make_response("ok", 200)
	return make_response("No such device", 200)