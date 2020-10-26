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
import time,serial,requests
from datetime import date,datetime,time
from flask_sqlalchemy import SQLAlchemy

from netScanner import map_network
app = Flask (__name__)

app.config['SECRET_KEY'] = "bdbgbn08Vtc4UV$bon(*0pnibuoyvtcr4R"
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///SmartSwitches.db'
db = SQLAlchemy(app)

arduinoSerialPort = '/dev/ttyACM0'


class Devices(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	ip = db.Column(db.String(100))
	device_key = db.Column(db.String(500),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	state = db.Column(db.Integer,nullable=False,default=0)
	description = db.Column(db.String(500))
	typeId = db.Column(db.Integer,db.ForeignKey("device_types.id"))
	date_added = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
	pins = db.relationship('Pins',backref='devices',lazy='joined')

	def json(self):
		device = {
			"id": self.id,
			"name": self.name,
			"ip": self.ip,
			"device_key": self.device_key,
			"command": self.command,
			"state": self.state,
			"description": self.description,
			"typeId": self.typeId,
			"date_added": self.date_added
		}
		return device


class Pins(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	action = db.Column(db.String(500))
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))
	
	def json(self):
		device = {
			"id": self.id,
			"name": self.name,
			"command": self.command,
			"description": self.description,
			"action": self.action,
			"deviceId": self.deviceId,
		}
		return device

class Device_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	devices = db.relationship('Devices',backref='device_types',lazy=True)


@app.route("/<deviceName>/<action>")
def action(deviceName, action):
	# example /room1sw/ON
	task=(deviceName+action)
	task_encode=task.encode()
	print(task)
	ser = serial.Serial(arduinoSerialPort)
	ser.baudrate = 9600
	ser.write(task_encode)
	print(task_encode)
	time.sleep(1)
	ser.close()


@app.route("/",methods=['GET','POST'])
def app_json():
	if request.method == 'POST':
		req = request.get_json()
		task = req["name"]
		task_encode=task.encode()
		ser = serial.Serial(arduinoSerialPort)
		ser.baudrate = 9600
		ser.write(task_encode)
		time.sleep(1)
		ser.close()
		response = {"name": task}
		return make_response(jsonify(response),200)


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
					return make_response("error, couldn't make a request (connection issue)",200)
			
			elif device.typeId == 3:
				try:
					r = requests.get('http://{}/control/?command={}'.format(device.ip, action))
					return make_response(jsonify(device.json()),200)
				except Exception as ex:
					return make_response("error, couldn't make a request (connection issue)")
			return make_response("error, couldn't make a request (no device found)",200)


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
					pin = Pins.query.filter_by(deviceId = device.id, command = pin_command).first()
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
		devices_data.append(info)
	return make_response(jsonify(devices_data),200)


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


# scanner function
@app.route("/scanNetwork/")
def scanNetwork():
	try:
		ip_addresses = map_network()
		print("scanning network, found data: {}".format(ip_addresses))
		for ip in ip_addresses:
				try:
					r = requests.get("http://{}/ping/".format(ip))
					print(r.text)
					device_command = r.text
					device = Devices.query.filter_by(command = command).first()
					if device:
						try:
							device.ip = ip
							db.session.commit()
						except Exception as ex:
							print(ex)

				except Exception as es:
					print("couldn't get data from an Ip {}".format(ip))
	except Exception as ex:
		print(ex)
	return "scanning done"

# # make scanning on reboot
# update_devices_ip()


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

'''
# teting /control/<state>
curl --header "Content-Type: application/json" \
	--request POST \
	--data '{"command":"test_local","state":1,"action":""}' \
	http://127.0.0.1:5000/esp/

# testing /control/?args
curl --header "Content-Type: application/json" \
	--request POST \
	--data '{"command":"test_local_json","pins":[{"command":"switch_mirror","action":"1"},{"command":"switch_AI","action":"activate"}]}' \
	http://127.0.0.1:5000/esp/JsonToArg/
'''

# optionalfunchtion for app init
def refresh_esp_states():
	for device in devices:
		try:
			r = requests.get('http://{}/control/{}'.format(device["ip"],device["state"]))
		except Exception as ex:
			print(ex)
	return "done"
# refresh_esp_states()


if __name__ == "__main__":
	app.run(host="0.0.0.0" , port=5000 , debug=True)