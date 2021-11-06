from flask import (
	request,
	jsonify,
	make_response
)
import requests

from main import app
from main import db

from main.models import (
	Device,
	Pin,
)

from main.scheduler.utils_scheduler import run_scheduled_task
from main.scheduler.manage_schedules import manage_schedules


@app.route("/esp/JsonToArg/",methods=['GET','POST'])
def esp_json_to_arg():
	isSchedule = request.args.get('isSchedule',0,type=int)
	toMaster = request.args.get('toMaster',0,type=int)

	if request.method == 'POST':
		req = request.get_json()

		command = req["command"]
		pins_json = req["pins"]

		device = Device.query.filter_by(command = command).first()
		if device:
			process_pins(device, pins_json)

			if device.toMaster == 1 or toMaster == 1:
				argumented_url_list = create_separated_device_typeId4_argumented_url_list(device)

				print(argumented_url_list)
				if (device.typeId == 4):
					remoteIp = device.ip
					print("getting typeid4 ip")
				else:
					remoteIp = device.master_device.ip
					print(device.master_device.ip)

				try:
					for pending_argument in argumented_url_list:
						argumented_url = create_argumented_url(pending_argument)
						r = requests.get('http://{}/control/?{}'.format(remoteIp, argumented_url))

					response = device.json()
					pins = [pin.json() for pin in device.pins]
					response['pins'] = pins

					# handle_schedule(device, isSchedule)
					return make_response(jsonify(response),200)

				except Exception as ex:
					print(ex)
					return make_response("error, couldn't make a device typeId=4 request (connection issue)")

			elif device.typeId == 2:
				pending_arguments = create_pending_arguments_from_device(device)
				argumented_url = create_argumented_url(pending_arguments)

				try:
					r = requests.get('http://{}/control/?{}'.format(device.ip, argumented_url))
					# !!! TODO: add validator and db insertion on "OK" response

					response = device.json()
					pins = [pin.json() for pin in device.pins]
					response['pins'] = pins

					# handle_schedule(device, isSchedule)
					return make_response(jsonify(response),200)

				except Exception as ex:
					print(ex)
					return make_response("error, couldn't make a device typeId=2 request (connection issue)")



		return make_response("error, device is not supported for current action",200)
	return make_response("error, couldn't make a request (no device found)",200)


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


def create_pending_arguments_from_device(device):
	pending_arguments = {}
	for pin in device.pins:
		pending_arguments[pin.command] = pin.action
	
	return pending_arguments


def create_argumented_url(pending_arguments):
	argumented_url = ""
	for key, value in pending_arguments.items():
		argumented_url += "{}={}&".format(key, value)

	return argumented_url


def create_separated_device_typeId4_argumented_url_list(device):
	argumented_url_list = []
	for pin in device.pins:
		current_arg = {}
		current_arg["command"] = pin.command
		current_arg["action"] = pin.action
		current_arg["process_key"] = pin.process_key
		current_arg[pin.command] = pin.action
		argumented_url_list.append(current_arg)

	return argumented_url_list


def handle_schedule(device, isSchedule):
	if not isSchedule:
		pinModels = [pin for pin in device.pins]
		manage_schedules(models = pinModels, models_name='pin')
	# if not isSchedule:
	# 	try:
	# 		if device.schedules:
	# 			for schedule in device.schedules:
	# 				print("called schedule")
	# 				run_scheduled_task(dbSchedule = schedule)
	# 	except Exception as ex:
	# 		print(ex)
	# 		print("schedule failed")