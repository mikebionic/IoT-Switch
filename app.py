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

class Device_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	devices = db.relationship('Devices',backref='device_types',lazy='joined')


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


@app.route("/esp/checkState/")
def check_state():
	devices = Devices.query.all()
	devices_data = [device.json() for device in devices]
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


# test function
@app.route("/control/<state>")
def control_state(state):
	print(state)
	return make_response("received state {}".format(state),200)

'''
curl --header "Content-Type: application/json" \
	--request POST \
	--data '{"command":"test_local","state":1}' \
	http://127.0.0.1:5000/esp/
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
