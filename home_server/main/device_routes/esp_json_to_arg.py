from flask import (
	Flask,
	request,
	jsonify,
	make_response
)
import requests

from main import app
from main import db

from main.models import (
	Devices,
	Pins,
	Sensors,
	Rooms,
	Triggers)
from main.utils_scheduler import run_scheduled_task


@app.route("/esp/JsonToArg/",methods=['GET','POST'])
def esp_json_to_arg():
	isSchedule = request.args.get('isSchedule',0,type=int)
	toMaster = request.args.get('toMaster',0,type=int)
	if request.method == 'POST':
		req = request.get_json()
		command = req["command"]
		pins_json = req["pins"]
		device = Devices.query.filter_by(command = command).first()
		if device:
			if device.typeId == 2:
				for pin in pins_json:
					pin_command = pin["command"]
					pin_action = pin["action"]
					pin = Pins.query\
					.filter_by(deviceId = device.id, command = pin_command)\
					.first()
					if pin:
						pin.action = pin_action
				db.session.commit()

				pending_arguments = {}
				for pin in device.pins:
					pending_arguments[pin.command] = pin.action

				argumented_url =""
				for key, value in pending_arguments.items():
					argumented_url += "{}={}&".format(key,value)

				try:
					remoteIp = device.ip
					if toMaster:
						remoteIp = app.config['MASTER_ARDUINO_IP']
					r = requests.get('http://{}/control/?{}'.format(remoteIp, argumented_url))
					response = device.json()
					pins = [pin.json() for pin in device.pins]
					response['pins'] = pins

					if not isSchedule:
						try:
							if device.schedules:
								for schedule in device.schedules:
									print("called schedule")
									run_scheduled_task(dbSchedule = schedule)
						except Exception as ex:
							print(ex)
							print("schedule failed")

					return make_response(jsonify(response),200)
				except Exception as ex:
					print(ex)
					return make_response("error, couldn't make a request (connection issue)")

		return make_response("error, device is not supported for current action",200)
	return make_response("error, couldn't make a request (no device found)",200)

