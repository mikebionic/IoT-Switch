from datetime import datetime

from main import db
from main.models import (
	Device,
)

from main.db_data_utils import save_device_from_json, merge_and_commit

def save_device_to_db(payload):

	payload["id"] = None
	payload["dateAdded"] = None

	device = Device.query.filter_by(device_key = payload["device_key"]).first()
	if device:
		if device.dateUpdated.timestamp() < payload["dateUpdated"]:
			device = merge_and_commit(device, save_device_from_json(payload))
			print("---------updating device---------")

	else:
		payload["dateUpdated"] = datetime.now()
		print("-------saving device;;;;;;")
		device = Device(**save_device_from_json(payload))
		db.session.add(device)
		db.session.commit()
	
	return device