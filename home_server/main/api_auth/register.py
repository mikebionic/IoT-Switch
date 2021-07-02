from flask import (
	make_response,
	request
)
from random import randint
from datetime import datetime, timedelta

from main import app, db
from main.models import Resident, QR_code
from main.core_utils.random_gen import random_gen

# "secret_key: "
# curl -i -H 'Authorization:Basic c2VjcmV0X2tleTpram4wOThoam5mZDkyaDNmZDJpb2pobmJjNzloMjNqZmMyNHVmMDI0Zmhu' http://127.0.0.1:5000/qr/request_register/
@app.route('/qr/request_register/')
def qr_request_register():
	auth = request.authorization

	status = 400
	response = {
		"secret_key": ""
	}

	try:
		if not auth:
			print("no auth")
			raise Exception
		resident = Resident.query.filter_by(secret_key = auth.password).first()
		if not resident:
			print("resident not found")
			raise Exception

		qr = QR_code()
		db.session.add(qr)
		db.session.commit()

		status = 200
		response["secret_key"] = qr.secret_key

	except Exception as ex:
		print(ex)
		return make_response(response), status

	return make_response(response), status


# curl --header "Content-Type: application/json" --request POST --data '{"secret_key":"kjn098hjnfd92h3fd2iojhnbc79h23jfc24uf024fhn"}' http://127.0.0.1:5000/qr/register/
@app.route('/qr/register/', methods=["POST"])
def qr_register():
	req = request.get_json()

	status = 400
	response = {
		"secret_key": ""
	}

	try:
		qr = req['secret_key']
		if not qr:
			print("no qr")
			raise Exception
		
		this_code = QR_code.query.filter_by(secret_key = qr).first()

		if not this_code:
			print("no such code")
			raise Exception

		if this_code.registered or this_code.dateAdded < datetime.now() - timedelta(minutes = 5):
			print("registered date or value issue")
			raise Exception
		
		qr_code = random_gen(20)
		if this_code.typeId != 1:
			this_code.registered = True
			qr_code = this_code.secret_key

		status = 200

		new_user = {
			"name": f"qr_user_{randint(1,99999)}",
			"secret_key": qr_code,
			"flatId": this_code.flatId
		}

		user = Resident(**new_user)
		db.session.add(user)
		db.session.commit()
		
		response["secret_key"] = qr_code
	
	except Exception as ex:
		print(ex)
		return make_response(response), status

	return make_response(response), status