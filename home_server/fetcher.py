import requests

from main.db_data_utils import save_device_to_db, save_pin_to_db

server_url = "https://ls.com.tm/"
server_path = ""
checkstate = "esp/checkState/"

full_url = f"{server_url}{server_path}{checkstate}"

def fetch_devices_and_pins():
	# try:
	r = requests.get(full_url)
	data = r.json()
	save_synched_data(data)
	# except Exception as e:
	# 	print(f"fetch error {e}")

def save_synched_data(data):
	for dev in data:
		device = save_device_to_db(dev)

		if dev["pins"]:
			for p in dev["pins"]:
				pin = save_pin_to_db(p, device)



# while 1:
fetch_devices_and_pins()