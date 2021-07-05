from flask import request, make_response, jsonify

from main import app
from main.models import (
	Sensor,
)

from main.db_data_utils import get_sensors_data

@app.route("/esp/get-sensors/")
def get_sensors():
	filtering = {}
	id = request.args.get("id",None,type=int)
	value = request.args.get("value","",type=str)
	secret_key = request.args.get("secret_key","",type=str)
	name = request.args.get("name","",type=str)
	command = request.args.get("command","",type=str)
	description = request.args.get("description","",type=str)
	master_device_id = request.args.get("master_device_id",None,type=int)
	deviceId = request.args.get("deviceId",None,type=int)
	typeId = request.args.get("typeId",None,type=int)

	if id:
		filtering["id"] = id
	if name:
		filtering["name"] = name
	if command:
		filtering["command"] = command
	if value:
		filtering["value"] = value
	if secret_key:
		filtering["secret_key"] = secret_key
	if description:
		filtering["description"] = description
	if master_device_id:
		filtering["master_device_id"] = master_device_id
	if deviceId:
		filtering["deviceId"] = deviceId
	if typeId:
		filtering["typeId"] = typeId

	sensors = Sensor.query.filter_by(**filtering).all()
	if sensors:
		sensor_data = get_sensors_data(db_models = sensors, with_records = True)
		if sensor_data:
			return make_response(jsonify(sensor_data), 200)

	return make_response(jsonify({"error":"Not found"}), 404)
