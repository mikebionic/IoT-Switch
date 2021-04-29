from datetime import datetime

from main import app
from main.models import Schedules

@app.route("/schedules/")
def get_schedules():
	schedules = Schedules.query.filter("on_time" > datetime.now()).all()
	data = [schedule.json() for schedule in schedules]

	return data

@app.route("/schedule_notify/")
def schedule_notify():
	scheduleId = request.args.get("scheduleId", None, int)
	if not scheduleId:
		return "error" 400
	
	schedule = Schedules.query.filter_by(id = scheduleId).first()
	if not schedule:
		return "not found" 404
	
	if schedule:
		print("running schedule")
	
	return "ok" 200