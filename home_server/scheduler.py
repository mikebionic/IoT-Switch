import requests
import json
from datetime import datetime, timedelta

server_url = "http://127.0.0.1:5000"
schedules_info_url = "/schedules/"
schedules_action_url = "/schedule_notify/"

# value in seconds
fetching_time_interval = 10

schedules_data = []

def get_schedules_info(
	server_url = server_url,
	schedules_info_url = schedules_info_url,
):
	r = requests.get(f"{server_url}{schedules_info_url}")
	print(r.text)
	try:
		res = r.json()
	except:
		res = []
	return res

def merge_schedule_datas(data, incoming_data):
	for item in incoming_data:
		data.append(item)
	
	data = list(set(data))
	data = [data for data in data]

	return data

def refresh_schedules():
	data = get_schedules_info()
	if data:
		schedules_data = merge_schedule_datas(schedules_data, data)
		schedules_data = order_datas_by_prop(schedules_data)

def order_datas_by_prop(
	data = schedules_data,
	prop = "on_time",
):
	data = (sorted(data, key = lambda i: i[prop]))
	return data

def send_schedule_action(
	data,
	server_url,
	schedules_action_url
):
	try:
		if not data:
			raise Exception
	
		r = requests.get(f"{server_url}{schedules_action_url}?scheduleId={data['id']}")
		print(r.text)

	except:
		print("failed to send action info")

def main():
	if str(datetime.now()) >= schedules_data[0]['on_time']:
		print('')