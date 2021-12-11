from main import db

from main.models import (
	Sensor_record
)

db.drop_all()
db.create_all()