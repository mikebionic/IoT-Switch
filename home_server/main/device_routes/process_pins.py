
from main import db
from main.models import Pin


def process_pins(device, pins_json):
	for pin in pins_json:
		pin_command = pin["command"]
		pin_action = pin["action"]
		pin = Pin.query\
		.filter_by(deviceId = device.id, command = pin_command)\
		.first()
		if pin:
			pin.action = pin_action
	db.session.commit()