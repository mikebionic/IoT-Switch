from datetime import datetime

from main import db
from main.models import (
	Pin,
)

from main.db_data_utils import save_pin_from_json, merge_and_commit
from main.scheduler.utils_scheduler import do_device_JsonToArg_req

def save_pin_to_db(payload, deviceModel):

	payload["id"] = None
	payload["dateAdded"] = None
	payload["deviceId"] = deviceModel.id

	pin = Pin.query.filter_by(command = payload["command"]).first()
	if pin:
		print("]]] found pin [[[")
		if pin.dateUpdated.timestamp() < payload["dateUpdated"]:
			print('----updating pin-------')
			pin = merge_and_commit(pin, save_pin_from_json(payload))
			do_device_JsonToArg_req(
				deviceModel,
				"/esp/JsonToArg/",
				pin.id,
				pin.action,
				deviceModel.command)

	else:
		print("}!! new pin !!{")
		payload["dateUpdated"] = datetime.now()
		print("-------saving new pin ;;;;;;;;;")
		pin = Pin(**save_pin_from_json(payload))
		db.session.add(pin)
		db.session.commit()
	
	return pin