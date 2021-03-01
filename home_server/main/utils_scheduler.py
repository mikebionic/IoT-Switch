import requests

def run_scheduled_task(dbSchedule):
	if dbSchedule.typeId == 1:
		device = dbSchedule.device
		current_pin = None
		for pin in device.Pins:
			if pin.id == pinId:
				print("found pin")
				current_pin = pin

		current_pin.action = dbSchedule.action
		db.session.commit

		payload = {
			"command": device.command
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
		playsound('./sounds/{}'.format(dbSchedule.path))