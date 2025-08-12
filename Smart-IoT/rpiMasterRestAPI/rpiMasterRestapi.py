from flask import Flask
app = Flask (__name__)
import time
import serial
from models import Switches

@app.route("/<deviceName>/<action>")
def action(deviceName, action):
	# example /room1sw/ON
	task=(deviceName+action)
	task_encode=task.encode()
	print(task)
	ser = serial.Serial('/dev/ttyUSB0')
	ser.baudrate = 9600
	ser.write(task_encode)
	time.sleep(1)
	ser.close()

@app.route("/get_data")
def arduino_data():
	command = "get_json_data"
	arduino.write(command)
	arduino_data = str(arduino.readline())
	return arduino_data


if __name__ == "__main__":
	app.run(host="0.0.0.0" , port=5000 , debug=True)
	
