from flask import request, make_response, jsonify

from main import app
from main.models import Device
from main.db_data_utils import get_device_data

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

	devices = Device.query.filter_by(**filtering).all()
	if devices:
		device_data = get_device_data(device_models = devices)
		if device_data:
			return make_response(jsonify(device_data), 200)
	return make_response(jsonify({"error":"Not found"}), 404)
