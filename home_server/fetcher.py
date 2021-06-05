import requests

from main import db
from main.models import (
	Devices,
	Pins,
	Sensors,
)

from main.scheduler import do_device_JsonToArg_req

server_url = "https://ip.com/"
server_path = "iot/"
checkstate = "esp/checkState/"

full_url = f"{server_url}{server_path}{checkstate}"

def fetch_devices_and_pins():
	try:
		r = requests.get(full_url)
		data = r.json()
		save_synched_data(data)
	except Exception as e:
		print(f"fetch error {e}")

def save_synched_data(data):
	for dev in data:
		device = Devices.query.filter_by(secret_key = dev["secret_key"])
		if device:
			if device.dateUpdated < dev["dateUpdated"]:
				device = merge_and_commit(device, dev)
				if dev["pins"]:
					for p in dev["pins"]:
						pin = Pins.query.filter_by(secret_key = p["secret_key"])
						if pin:
							if pin.dateUpdated < p["dateUpdated"]:
								pin = merge_and_commit(pin, p)
								do_device_JsonToArg_req(
									device,
									"/esp/JsonToArg/",
									pin.pinId,
									pin.pin_action,
									pin.device_command)

						else:
							pin = Pins(**p)
							db.session.add(pin)
							db.session.commit()

		else:
			device = Devices(**data)
			db.session.add(device)
			db.session.commit()



def merge_and_commit(db_entity, payload):
	db_entity.do_update(**payload)
	db.session.commit()
	return db_entity
	# do request here()