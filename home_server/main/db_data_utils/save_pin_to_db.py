from datetime import datetime

from main import db
from main.models import (
	Pins,
)

from main.db_data_utils import save_pin_from_json, merge_and_commit
from main.scheduler.utils_scheduler import do_device_JsonToArg_req

def save_pin_to_db(payload, deviceModel):

	payload["id"] = None
	payload["dateAdded"] = None
	payload["deviceId"] = deviceModel.id

	pin = Pins.query.filter_by(secret_key = payload["secret_key"]).first()
	if pin:
		if pin.dateUpdated.timestamp() < payload["dateUpdated"]:
			print('----updating pin-------')
			pin = merge_and_commit(pin, save_pin_from_json(payload))
			do_device_JsonToArg_req(
				deviceModel,
				"/esp/JsonToArg/",
				pin.pinId,
				pin.pin_action,
				pin.device_command)

	else:
		payload["dateUpdated"] = datetime.now()
		print("-------saving new pin ;;;;;;;;;")
		pin = Pins(**save_pin_from_json(payload))
		db.session.add(pin)
		db.session.commit()
	
	return pin