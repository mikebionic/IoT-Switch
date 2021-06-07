import requests
from datetime import datetime

from main import db
from main.models import (
	Devices,
	Pins,
	Sensors,
)
from main.db_data_utils import save_device_from_json, save_pin_from_json

from main.scheduler.utils_scheduler import do_device_JsonToArg_req

server_url = "https://ls.com.tm/"
server_path = ""
checkstate = "esp/checkState/"

full_url = f"{server_url}{server_path}{checkstate}"

def fetch_devices_and_pins():
	# try:
	r = requests.get(full_url)
	data = r.json()
	# print(data)
	save_synched_data(data)
	# except Exception as e:
	# 	print(f"fetch error {e}")

def save_synched_data(data):
	for dev in data:
		print(dev)
		device = Devices.query.filter_by(command = dev["command"]).first()
		if device:
			if device.dateUpdated.timestamp() < dev["dateUpdated"]:
				device = merge_and_commit(device, save_device_from_json(dev))
				if dev["pins"]:
					for p in dev["pins"]:
						pin = Pins.query.filter_by(secret_key = p["secret_key"]).first()
						if pin:
							if pin.dateUpdated.timestamp() < p["dateUpdated"]:
								pin = merge_and_commit(pin, save_pin_from_json(p))
								do_device_JsonToArg_req(
									device,
									"/esp/JsonToArg/",
									pin.pinId,
									pin.pin_action,
									pin.device_command)

						else:
							p["id"] = None
							p["dateAdded"] = None
							p["dateUpdated"] = datetime.now()
							pin = Pins(**save_pin_from_json(p))
							db.session.add(pin)
							db.session.commit()

		else:
			dev["id"] = None
			dev["dateAdded"] = None
			dev["dateUpdated"] = datetime.now()
			device = Devices(**save_device_from_json(dev))
			db.session.add(device)
			db.session.commit()



def merge_and_commit(db_entity, payload):
	payload["id"] = None
	payload["dateAdded"] = db_entity.dateAdded
	payload["dateUpdated"] = datetime.now()
	db_entity.do_update(**payload)
	db.session.commit()
	print("make request with updates")
	return db_entity
	# do request here()

# while 1:
fetch_devices_and_pins()