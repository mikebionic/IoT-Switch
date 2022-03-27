from flask import request
from sqlalchemy.orm import joinedload

from main import app
from main.models import Resident, Device, Flat
from main.db_data_utils import get_devices_data

@app.route("/get-device-by-user/")
def get_device_by_user():
	username = request.args.get("username","",type=str)
	password = request.args.get("password","",type=str)

	this_user = Resident.query\
		.filter_by(
			username = username,
			password = password
		)\
		.options(
			joinedload(Resident.flat)\
				.options(joinedload(Flat.devices))
		)\
		.first_or_404()

	if this_user.flat:
		return get_devices_data(db_models=[device for device in this_user.flat.devices])

	return "ok"