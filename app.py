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

app = Flask (__name__)


arduinoSerialPort = '/dev/ttyACM0'

esp_devices_data = [
	{
		"name": "Lights Hall",
		"ip": "192.168.1.145",
		"state": 0,
		"command": "lights_hall",
		"description": "Turns on/off hall lights"
	},
	{
		"name": "Lights Kitchen",
		"ip": "192.168.1.121",
		"state": 0,
		"command": "lights_kitchen",
		"description": "Turns on/off kitchen lights"
	},
	{
		"name": "Local test",
		"ip": "127.0.0.1:5000",
		"state": 0,
		"command": "test_local",
		"description": "Turns on/off Local test"
	}
]


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
		for device in esp_devices_data:
			if device["command"] == command:
				try:
					device["state"] = state
					r = requests.get('http://{}/control/{}'.format(device["ip"],device["state"]))
					print (r.text)
					return make_response(jsonify(device),200)
				except Exception as ex:
					return make_response("error, couldn't make a request (no device found)",200)
		return make_response("error, couldn't make a request (no device found)",200)

@app.route("/esp/checkState/")
def check_state():
	return make_response(jsonify(esp_devices_data),200)


@app.route("/esp/setState/")
def setEspState():
	command = request.args.get('command')
	state = request.args.get('state')

	for device in esp_devices_data:
		if device["command"] == command:
			try:
				device["state"] = state
				print(device)
				return make_response("ok",200)
			except Exception as ex:
				return make_response("err",200)


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
	for device in esp_devices_data:
		try:
			r = requests.get('http://{}/control/{}'.format(device["ip"],device["state"]))
		except Exception as ex:
			print(ex)
	return "done"
# refresh_esp_states()


if __name__ == "__main__":
	app.run(host="0.0.0.0" , port=5000 , debug=True)