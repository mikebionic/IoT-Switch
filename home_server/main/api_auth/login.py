from flask import (
	make_response,
	request
)
import jwt
from datetime import datetime
import datetime as dt

from main import app
from main.models import Resident
from main.config import Config


# curl -i -H 'Authorization:Basic c2VjcmV0X2tleTpram4wOThoam5mZDkyaDNmZDJpb2pobmJjNzloMjNqZmMyNHVmMDI0Zmhu' http://127.0.0.1:5000/qr/login/
@app.route('/device/login/')
def device_login():
	auth = request.authorization

	status = 400
	response = {
		"data": "",
		"info": "Login failed"
	}

	try:
		if not auth:
			print("not auth")
			raise Exception
		resident = Resident.query.filter_by(username = auth.username).first()
		if not resident:
			print("no resident found")
			raise Exception
		if resident.password != auth.password:
			raise Exception

		status = 200

		exp = datetime.now() + dt.timedelta(minutes = Config.AUTH_TOKEN_EXP_TIME_MINUTES)
		auth_token = jwt.encode(
			{"id": Resident.id, "secret_key": Resident.secret_key, "exp": exp},
			Config.SECRET_KEY
		)
		response["data"] = auth_token
		response["info"] = "Login success"

	except:
		return make_response(response), status

	return make_response(response), status


@app.route('/qr/login/')
def qr_login():
	auth = request.authorization

	status = 400
	response = {
		"data": "",
		"info": "Login failed"
	}

	try:
		if not auth:
			print("no auth")
			raise Exception
		resident = Resident.query.filter_by(secret_key = auth.password).first()
		if not resident:
			print("no resident found")
			raise Exception

		status = 200

		exp = datetime.now() + dt.timedelta(minutes = Config.AUTH_TOKEN_EXP_TIME_MINUTES)
		auth_token = jwt.encode(
			{"id": resident.id, "secret_key": resident.secret_key, "exp": exp},
			Config.SECRET_KEY
		)
		response["data"] = auth_token
		response["info"] = "Login success"


	except Exception as ex:
		print(ex)
		return make_response(response), status

	return make_response(response), status