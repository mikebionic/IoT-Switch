import requests
import os, sys
from flask import json
from time import sleep

from main import app, db
from main.models import Devices
local_addr = app.config['SERVER_URL']

if app.config['SOUND_PLAYER'] == "playsound":
	from playsound import playsound


def run_scheduled_task(dbSchedule):
	if dbSchedule.typeId == 1:
		device = Devices.query.filter_by(command = dbSchedule.device_command).first()
		if device:
			print(device.json())
			current_pin = None
			for pin in device.pins:
				if pin.id == dbSchedule.pinId:
					print("found pin")
					current_pin = pin

			current_pin.action = dbSchedule.pin_action
			db.session.commit()

			payload = {
				"command": dbSchedule.device_command,
				"pins": [
					{
						"command": current_pin.command,
						"action": current_pin.action
					}
				]
			}

			print(payload)

			r = requests.post(
				"{}{}{}".format(local_addr, dbSchedule.url,"?isSchedule=1"),
				data = json.dumps(payload),
				headers = {'Content-Type': 'application/json'})

	elif dbSchedule.typeId == 2:
		if app.config['SOUND_PLAYER'] == "omxplayer":
			sleep(0.3)
			os.system('omxplayer -o both main/sounds/{} &'.format(dbSchedule.path))
			sleep(1)
			sys.exit()
		
		elif app.config['SOUND_PLAYER'] == "playsound":
			playsound('main/sounds/{}'.format(dbSchedule.path))

	return True