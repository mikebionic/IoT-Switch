from flask import Flask, make_response
import requests

from main import app, db

from .models import Device, Master_device
from .netScanner import map_network


@app.route("/scanNetwork/")
def scanNetwork():
	try:
		print("requested scanning")
		ip_addresses = map_network()
		print("scanning network, found data: {}".format(ip_addresses))
		for ip in ip_addresses:
				try:
					r = requests.get("http://{}/ping/".format(ip))
					print(r.text)
					device_command = r.text
					device = Device.query.filter_by(device_key = device_command).first()
					if device:
						try:
							device.ip = ip
							db.session.commit()
						except Exception as ex:
							print(ex)

					master_device = Master_device.query.filter_by(device_key = device_command).first()
					if master_device:
						try:
							master_device.ip = ip
							print("added master dev ip")
							db.session.commit()
						except Exception as ex:
							print(ex)

				except Exception as ex:
					print("couldn't get data from an Ip {}, {}".format(ip, ex))
	except Exception as ex:
		print(ex)
	return make_response("scanning done",200)