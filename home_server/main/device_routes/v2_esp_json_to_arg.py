
from flask import request, make_response

from main import app
from main.models import Master_device, Device
from .make_device_request import make_device_request


@app.route("/esp/v2/JsonToArg/",methods=['GET','POST'])
def v2_esp_json_to_arg():
	isSchedule = request.args.get('isSchedule',0,type=int)
	master_device = request.args.get('master_device',0,type=int)
	if request.method == 'POST':
		req = request.get_json()

		command = req["command"]
		pins_json = req["pins"]

		if master_device:
			master_device = Master_device.query.filter_by(command = command).first()
			devices = master_device.devices
			statuses = []
			res = []
			for device in devices:
				resp, status, message = make_device_request(device, pins_json)
				statuses.append(status)
				res.append(resp)
			
			status = 0
			for s in statuses:
				if s != 0:
					status = 1
		
		else:
			device = Device.query.filter_by(command = command).first()
			if device:
				res, status, message = make_device_request(device, pins_json)

		if status == 0:
			return make_response(message, 200)

		else:
			return make_response(res, 200)

		return make_response("error, device is not supported for current action",200)
	return make_response("error, couldn't make a request (no device found)",200)



