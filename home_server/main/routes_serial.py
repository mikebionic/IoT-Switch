import serial, time

from main import app

arduinoSerialPort = '/dev/ttyACM0'


@app.route("/<deviceName>/<action>")
def action(deviceName, action):
	# example /room1sw/ON
	task = (deviceName + action)
	task_encode = task.encode()
	print(task)
	ser = serial.Serial(arduinoSerialPort)
	ser.baudrate = 9600
	ser.write(task_encode)
	print(task_encode)
	time.sleep(1)
	ser.close()


@app.route("/serial",methods=['GET','POST'])
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