
from main.models import Schedule

def manage_schedules(models, models_name):
	if models_name == "pin":
		for model in models:
			schedule = Schedule.query\
				.filter_by(
					pinId = model.id,
					on_action = model.action,
				).first()
			if schedule:
				# run_schedule()
				print("running pin schedule")
				pass

	elif models_name == "device":
		for model in models:
			schedule = Schedule.query\
				.filter_by(
					deviceId = model.id,
					on_command = model.command,
				).first()
			if schedule:
				# run_schedule()
				print("running device schedule")
				pass

	elif models_name == "sensor":
		for model in models:
			schedule = Schedule.query\
				.filter_by(
					sensorId = model.id,
					on_value = model.value,
				).first()
			if schedule:
				# run_schedule()
				print("running sensor schedule")
				pass


def handle_schedule(device, isSchedule):
	if not isSchedule:
		pinModels = [pin for pin in device.pins]
		manage_schedules(models = pinModels, models_name='pin')
	# if not isSchedule:
	# 	try:
	# 		if device.schedules:
	# 			for schedule in device.schedules:
	# 				print("called schedule")
	# 				run_scheduled_task(dbSchedule = schedule)
	# 	except Exception as ex:
	# 		print(ex)
	# 		print("schedule failed")