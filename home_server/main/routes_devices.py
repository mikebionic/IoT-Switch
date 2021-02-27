from flask import (
	Flask,
	render_template,
	url_for,
	flash,
	redirect,
	request,
	Response,
	jsonify,
	make_response)
import time, requests
from datetime import date, datetime
# from flask_socketio import SocketIO, emit

from main import app
from main import db

from .models import (
	Devices,
	Pins,
	Sensors,
	Rooms,
	Triggers)


@app.route("/esp/",methods=['GET','POST'])
def esp():
	if request.method == 'POST':
		req = request.get_json()
		state = req["state"]
		command = req["command"]
		action = req["action"]
		device = Devices.query.filter_by(command = command).first()
		if device:
			if device.typeId == 1:
				try:
					device.state = state
					r = requests.get('http://{}/control/{}'.format(device.ip, device.state))
					db.session.commit()
					print (r.text)
					return make_response(jsonify(device.json()),200)
				except Exception as ex:
					return make_response("error, couldn't make a request (connection issue) {}".format(ex),200)
			
			elif device.typeId == 3:
				try:
					r = requests.get('http://{}/control/?command={}'.format(device.ip, action))
					return make_response(jsonify(device.json()),200)
				except Exception as ex:
					return make_response("error, couldn't make a request (connection issue)")
			return make_response("error, couldn't make a request (no device found)",200)


@app.route("/triggers/",methods=['GET','POST'])
def triggers():
	if request.method == 'POST':
		req = request.get_json()
		state = req["state"]
		command = req["command"]
		action = req["action"]
		trigger = Triggers.query.filter_by(command = command).first()
		if trigger:
			trigger.state = state
			db.session.commit()
			return make_response(jsonify(trigger.json()),200)
		else:
			return make_response("No such trigger",200)


@app.route("/esp/motionAlert/",methods=['GET','POST'])
def esp_motionAlert():
	device_key = request.args.get('device_key')
	state = request.args.get('state')

	device = Devices.query.filter_by(device_key = device_key).first()
	if device:
		triggers.query.filter_by(command = "motion_trigger").first()
		if trigger:
			if (trigger.state == 1):
				try:
					device.state = state
					db.session.commit()
				except Exception as ex:
					return make_response("err",200)
		return make_response("ok",200)


@app.route("/reset_sensors/",methods=['GET'])
def reset_sensors():
	try:
		sensorId = request.args.get('sensorId')
	except:
		sensorId = None
	try:
		sensorCommand = request.args.get('sensorCommand')
	except:
		sensorCommand = None

	if sensorCommand:
		sensor = Sensors.query.filter_by(command = sensorCommand).first()
		sensor.value == 0.0

	else:
		sensors = Sensors.query.all()
		for sensor in sensors:
			sensor.value == 0.0
	db.session.commit()
	return make_response("ok",200)


# restarting esp device
@app.route("/send_device_reset/",methods=['GET'])
def send_device_reset():
	device_command = request.args.get('device_command')
	device = Devices.query.filter_by(command = device_command).first()
	if device:
		try:
			r = requests.get("http://{}/reset".format(device.ip))
		except Exception as ex:
			return make_response("Couldnt make a request {}".format(ex))
		return make_response("OK")
	return make_response("No such device")


# reconnect esp device to Wifi AP
@app.route("/send_device_reconnect/",methods=['GET'])
def send_device_reconnect():
	device_command = request.args.get('device_command')
	device = Devices.query.filter_by(command = device_command).first()
	if device:
		try:
			r = requests.get("http://{}/reconnect".format(device.ip))
		except Exception as ex:
			return make_response("Couldnt make a request {}".format(ex))
		return make_response("OK")
	return make_response("No such device")


# esp's sensor recording feature (record values)
@app.route("/esp/ArgToDB/",methods=['GET'])
def esp_arg_to_db():
	device_key = request.args.get('device_key')
	pin_sensor_command = request.args.get('command')
	try:
		value = request.args.get('value')
	except:
		value = None

	try:
		action = request.args.get('action')
	except:
		action = None

	device = Devices.query.filter_by(device_key = device_key).first()
	if device:
		if action:
			try:
				pin = Pins.query\
				.filter_by(deviceId = device.id, command = pin_sensor_command)\
				.first()

				if pin:
					pin.action = action
					db.session.commit()
					# print(device.name)
					return make_response("ok",200)
				return make_response("not Found",200)
			except Exception as ex:
				return make_response("err",200)

		if value:
			try:
				sensor = Sensors.query\
				.filter_by(deviceId = device.id, command = pin_sensor_command)\
				.first()
				if sensor:
					if sensor.typeId == 1:
						sensor.value += float(value)
					elif sensor.typeId == 2:
						sensor.value = float(value)
					db.session.commit()
					# print(device.name)
					return make_response("ok",200)
				return make_response("not Found",200)
			except Exception as ex:
				return make_response("err",200)


# record esp's ip address to db
@app.route("/esp/ping/")
def esp_ping():
	device_key = request.args.get('device_key')
	ip_address = request.args.get('ip_address')
	# command = request.args.get('command')
	device = Devices.query.filter_by(device_key = device_key).first()
	if device:
		try:
			device.ip = ip_addresshttps://www.ubuntupit.com/install-adapta-kde-theme-ubuntu-kde-plasma/
			db.session.commit()
		except Exception as ex:
			print(ex)
			return make_response("err", 200)
		return make_response("ok", 200)
	return make_response("No such device", 200)


@app.route("/esp/JsonToArg/",methods=['GET','POST'])
def esp_json_to_arg():
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
					r = requests.get('http://{}/control/?{}'.format(device.ip, argumented_url))
					response = device.json()
					print(response)
					pins = [pin.json() for pin in device.pins]
					print(pins)
					response['pins'] = pins
					print(response)
					return make_response(jsonify(response),200)
				except Exception as ex:
					return make_response("error, couldn't make a request (connection issue)")
		return make_response("error, device is not supported for current action",200)
	return make_response("error, couldn't make a request (no device found)",200)


@app.route("/esp/checkState/")
def check_state():
	devices = Devices.query.all()
	devices_data = []
	for device in devices:
		info = device.json()
		pins = [pin.json() for pin in device.pins]
		info['pins'] = pins
		sensors = [sensor.json() for sensor in device.sensors]
		info['sensors'] = sensors
		devices_data.append(info)
	return make_response(jsonify(devices_data),200)


@app.route("/esp/getDevice/")
def getDevice():
	filtering = {}
	barcode = request.args.get("barcode","",type=str)
	name = request.args.get("name","",type=str)
	command = request.args.get("command","",type=str)
	ip = request.args.get("ip","",type=str)
	if barcode:
		filtering["barcode"] = barcode
	if name:
		filtering["name"] = name
	if command:
		filtering["command"] = command
	if ip:
		filtering["ip"] = ip
	device = Devices.query.filter_by(**filtering).first()
	if device:
		return make_response(jsonify(device.json()), 200)
	return make_response(jsonify({"error":"Not found"}), 404)


@app.route("/esp/setState/")
def setEspState():
	device_key = request.args.get('device_key')
	state = request.args.get('state')

	device = Devices.query.filter_by(device_key = device_key).first()
	if device:
		try:
			device.state = state
			db.session.commit()
			print(device.name)
			return make_response("ok",200)
		except Exception as ex:
			return make_response("err",200)


@app.route("/esp/detectWater/")
def detectWater():
	device_key = request.args.get('device_key')
	state = request.args.get('state')
	
	pump_device_command = "water_pump"

	device = Devices.query.filter_by(device_key = device_key).first()
	if device:
		try:
			device.state = 1
			db.session.commit()

			try:
				pump_device = Devices.query.filter_by(device_key = pump_device_command).first()
				pump_state = 1
				pump_device.state = pump_state
				db.session.commit()
				r = requests.get('http://{}/control/{}'.format(pump_device.ip, pump_state))
			except Exception as ex:
				print("error, couldn't make a request (connection issue)",200)

			print(device.name)
			return make_response("ok",200)
		except Exception as ex:
			return make_response("err",200)


# test functions
@app.route("/control/<state>")
def control_state(state):
	print(state)
	return make_response("received state {}".format(state),200)


@app.route("/control/")
def control_args():
	args = request.args
	print(args)
	return make_response("received args {}".format(args),200)


# optionalfunchtion for app init
def refresh_esp_states():
	for device in devices:
		try:
			r = requests.get('http://{}/control/{}'.format(device["ip"],device["state"]))
		except Exception as ex:
			print(ex)
	return "done"
# refresh_esp_states()