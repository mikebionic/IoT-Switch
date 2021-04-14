from flask import (
	render_template,
	redirect,
	make_response,
	jsonify,
	request
)
from random import randint
from datetime import datetime, timedelta

from main import app, db
from main.models import Residents, QR_codes

@app.route('/login')
def admin_login():
	return render_template('login/login.html')

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
		resident = Residents.query.filter_by(secret_key = auth.password).first()
		if not resident:
			print("resident not found")
			raise Exception

		qr = QR_codes()
		db.session.add(qr)
		db.session.commit()

		status = 200
		response["secret_key"] = qr.secret_key

	except Exception as ex:
		print(ex)
		return make_response(response), status

	return make_response(response), status

# curl -i -H 'Authorization:Basic c2VjcmV0X2tleTpram4wOThoam5mZDkyaDNmZDJpb2pobmJjNzloMjNqZmMyNHVmMDI0Zmhu' http://127.0.0.1:5000/qr/login/
@app.route('/device/login/')
def device_login():
	auth = request.authorization

	status = 400
	response = {
		"data": "Login failed!"
	}

	try:
		if not auth:
			raise Exception
		resident = Residents.query.filter_by(username = auth.username).first()
		if not resident:
			raise Exception
		if resident.password != auth.password:
			raise Exception

		status = 200
		response["data"] = "Login success"

	except:
		return make_response(response), status

	return make_response(response), status


# curl --header "Content-Type: application/json" --request POST --data '{"secret_key":"kjn098hjnfd92h3fd2iojhnbc79h23jfc24uf024fhn"}' http://127.0.0.1:5000/qr/register/
@app.route('/qr/register/', methods=["POST"])
def qr_register():
	req = request.get_json()

	status = 400
	response = {
		"data": "Register failed!"
	}

	try:
		qr = req['secret_key']
		if not qr:
			print("no qr")
			raise Exception
		
		code = QR_codes.query.filter_by(secret_key = qr).first()

		if not code:
			print("no such code")
			raise Exception

		if code.registered or code.dateAdded < datetime.now() - timedelta(minutes = 5):
			print("registered date or value issue")
			raise Exception
		
		qr_code = None
		if code.typeId != 1:
			code.registered = True
			qr_code = code.secret_key

		status = 200
		new_user = {
			"name": f"qr_user_{randint(1,99999)}",
			"secret_key": qr_code
		}

		user = Residents(**new_user)
		db.session.add(user)
		db.session.commit()
		
		response["data"] = "Register success"
	
	except Exception as ex:
		print(ex)
		return make_response(response), status

	return make_response(response), status


@app.route('/qr/login/')
def qr_login():
	auth = request.authorization

	status = 400
	response = {
		"data": "Login failed!"
	}

	try:
		if not auth:
			raise Exception
		resident = Residents.query.filter_by(secret_key = auth.password).first()
		if not resident:
			raise Exception

		status = 200
		response["data"] = "Login success"

	except:
		return make_response(response), status

	return make_response(response), status