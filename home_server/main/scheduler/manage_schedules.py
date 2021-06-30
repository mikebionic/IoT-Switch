
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

