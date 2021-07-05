from flask import request, make_response, jsonify

from main import app
from main.models import Device
from main.db_data_utils import get_devices_data

@app.route("/esp/getDevice/")
def getDevice():
	filtering = {}

	barcode = request.args.get("barcode","",type=str)
	name = request.args.get("name","",type=str)
	ip = request.args.get("ip","",type=str)
	barcode = request.args.get("barcode","",type=str)
	command = request.args.get("command","",type=str)
	device_key = request.args.get("device_key","",type=str)
	secret_key = request.args.get("secret_key","",type=str)
	state = request.args.get("state","",type=str)
	description = request.args.get("description","",type=str)
	master_device_id = request.args.get("master_device_id",None,type=int)
	typeId = request.args.get("typeId",None,type=int)
	flatId = request.args.get("flatId",None,type=int)
	roomId = request.args.get("roomId",None,type=int)

	if barcode:
		filtering["barcode"] = barcode
	if name:
		filtering["name"] = name
	if command:
		filtering["command"] = command
	if ip:
		filtering["ip"] = ip
	if device_key:
		filtering["device_key"] = device_key
	if secret_key:
		filtering["secret_key"] = secret_key
	if state:
		filtering["state"] = state
	if description:
		filtering["description"] = description
	if master_device_id:
		filtering["master_device_id"] = master_device_id
	if typeId:
		filtering["typeId"] = typeId
	if flatId:
		filtering["flatId"] = flatId
	if roomId:
		filtering["roomId"] = roomId

	devices = Device.query.filter_by(**filtering).all()
	if devices:
		device_data = get_devices_data(db_models = devices)
		if device_data:
			return make_response(jsonify(device_data), 200)
	return make_response(jsonify({"error":"Not found"}), 404)
