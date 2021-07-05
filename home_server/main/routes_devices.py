from flask import (
	Flask,
	render_template,
	url_for,
	flash,
	redirect,
	request,
	abort,
	Response,
	jsonify,
	make_response)
import time, requests
from datetime import date, datetime
# from flask_socketio import SocketIO, emit

from main import app
from main import db

from .models import (
	Device,
	Pin,
	Sensor,
	Room,
	Trigger,
	Resident)
from main.scheduler.utils_scheduler import run_scheduled_task
from main.db_data_utils.get_devices_data import get_devices_data


@app.route("/esp/",methods=['GET','POST'])
def esp():
	# !!! deprecated, now uses device typeId=4
	toMaster = request.args.get('toMaster',0,type=int)
	if request.method == 'POST':
		req = request.get_json()
		state = req["state"]
		command = req["command"]
		action = req["action"]
		device = Device.query.filter_by(command = command).first()
		if device:

			remoteIp = device.ip
			# !!! deprecated
			if toMaster:
				remoteIp = app.config['MASTER_ARDUINO_IP']

			if device.typeId == 1:
				try:
					device.state = state
					r = requests.get('http://{}/control/{}'.format(remoteIp, device.state))
					db.session.commit()
					print (r.text)
					return make_response(jsonify(device.json()),200)
				except Exception as ex:
					return make_response("error, couldn't make a request (connection issue) {}".format(ex),200)
			
			elif device.typeId == 3:
				try:
					r = requests.get('http://{}/control/?command={}'.format(remoteIp, action))
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
		trigger = Trigger.query.filter_by(command = command).first()
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

	device = Device.query.filter_by(device_key = device_key).first()
	if device:
		trigger = Trigger.query.filter_by(command = "motion_trigger").first()
		if trigger:
			trigger.state = state
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
		sensor = Sensor.query.filter_by(command = sensorCommand).first()
		sensor.value == 0.0
	
	elif sensorId:
		sensor = Sensor.query.filter_by(id = sensorId).first()
		sensor.value == 0.0	

	else:
		sensors = Sensor.query.all()
		for sensor in sensors:
			sensor.value == 0.0
	db.session.commit()
	return make_response("ok",200)


# restarting esp device
@app.route("/send_device_reset/",methods=['GET'])
def send_device_reset():
	device_command = request.args.get('device_command')
	device = Device.query.filter_by(command = device_command).first()
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
	device = Device.query.filter_by(command = device_command).first()
	if device:
		try:
			r = requests.get("http://{}/reconnect".format(device.ip))
		except Exception as ex:
			return make_response("Couldnt make a request {}".format(ex))
		return make_response("OK")
	return make_response("No such device")


@app.route("/esp/checkState/")
def check_state():
	# print(request.headers)
	# if 'resident-key' not in request.headers:
	# 	print("notin")
	# 	abort(401)
	# print(request.headers['resident-key'])
	# secret_key = request.headers['resident-key']
	# resident = Resident.query.filter_by(secret_key = secret_key).first()
	# print(resident.name)
	data = get_devices_data()
	return make_response(jsonify(data),200)


@app.route("/esp/setState/")
def setEspState():
	device_key = request.args.get('device_key')
	state = request.args.get('state')

	device = Device.query.filter_by(device_key = device_key).first()
	if device:
		try:
			device.state = state
			db.session.commit()
			print(device.name)
			return make_response("ok",200)
		except Exception as ex:
			print(ex)
			return make_response("err",200)


@app.route("/esp/detectWater/")
def detectWater():
	device_key = request.args.get('device_key')
	state = request.args.get('state')
	
	pump_device_command = "water_pump"

	device = Device.query.filter_by(device_key = device_key).first()
	if device:
		try:
			device.state = 1
			db.session.commit()

			try:
				pump_device = Device.query.filter_by(device_key = pump_device_command).first()
				pump_state = 1
				pump_device.state = pump_state
				db.session.commit()
				r = requests.get('http://{}/control/{}'.format(pump_device.ip, pump_state))
			except Exception as ex:
				print(f"error, couldn't make a request (connection issue) {ex}",200)

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
	devices = Device.query.all()
	for device in devices:
		try:
			r = requests.get('http://{}/control/{}'.format(device["ip"],device["state"]))
		except Exception as ex:
			print(ex)
	return "done"
# refresh_esp_states()