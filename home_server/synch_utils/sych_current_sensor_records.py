import requests

from main import db
from main.models import Sensor, Sensor_record
from main.config import Config

sych_server_host = "http://localhost:5000/"
sych_url_path = "get_flat_sensors/"
flat_secret_key = Config.FLAT_SECRET_KEY

# sample_response = {
#   "command": "current_measurer", 
#   "dateAdded": "Tue, 18 Jan 2022 09:52:15 GMT", 
#   "dateUpdated": 1642481717.031364, 
#   "description": "Measured amount of electricity", 
#   "deviceId": null, 
#   "flatId": 1, 
#   "id": 991, 
#   "master_device_id": null, 
#   "name": "Current measurer", 
#   "secret_key": "YrwxipqXaEoqYGH7Qnb8KJl1zIacP2dFgCSejD6sXXZUS2t8eC2Jzq07opszU3A46XJdDpbrCvXVTwl9eqq9pz8H8GlFQnaDAoV8", 
#   "sensor_records": [
#     {
#       "date": "Tue, 18 Jan 2022 00:00:00 GMT", 
#       "dateAdded": "Tue, 18 Jan 2022 09:52:34 GMT", 
#       "dateUpdated": 1642481718.380535, 
#       "description": null, 
#       "deviceId": null, 
#       "flatId": 1, 
#       "id": 1, 
#       "master_device_id": null, 
#       "name": null, 
#       "secret_key": "voMLFnmmTdRM2IypNMnURk4Nc4VhWRTLfsByTdOsnhQbb72kCEsaTU911r6oiMcKbGt5kinU6A0wy6dQs7vNoOclXEf8BlMiVFtO", 
#       "sensorId": 991, 
#       "value": 52.0
#     }
#   ], 
#   "typeId": 1, 
#   "value": 52.0
# }

def make_synch_request():
	data = None
  try:
    r = requests.get(f"{sych_server_host}/{sych_url_path}?flat_key={flat_secret_key}")
    print(r.text())
    data = r.json()
	except Exception as e:
	  print(e)

	return data