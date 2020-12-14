from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from datetime import date,datetime,time

from devices_config import devices, pins, sensors, rooms
from default_devices_config import device_types, sensor_types, triggers

app = Flask (__name__)
app.config['SECRET_KEY'] = "bdbgbn08Vtc4UV$bon(*0pnibuoyvtcr4R"
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///SmartSwitches.db'

db = SQLAlchemy(app)


class City(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(500),nullable=False)
	description = db.Column(db.String(500))
	typeId = db.Column(db.Integer,db.ForeignKey("city_types.id"))
	dateAdded = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
	regions = db.relationship('Regions',backref='city',lazy=True)


class Regions(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(500),nullable=False)
	description = db.Column(db.String(500))
	cityId = db.Column(db.Integer,db.ForeignKey("city.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("region_types.id"))
	dateAdded = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
	houses = db.relationship('Houses',backref='regions',lazy=True)


class Houses(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(500),nullable=False)
	description = db.Column(db.String(500))
	longit = db.Column(db.String(100))
	latit = db.Column(db.String(100))
	regionId = db.Column(db.Integer,db.ForeignKey("regions.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("house_types.id"))
	dateAdded = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
	flats = db.relationship('Flats',backref='houses',lazy=True)


class Flats(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(500),nullable=False)
	description = db.Column(db.String(500))
	houseId = db.Column(db.Integer,db.ForeignKey("houses.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("flat_types.id"))
	dateAdded = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
	residents = db.relationship('Residents',backref='flats',lazy=True)
	devices = db.relationship('Devices',backref='flats',lazy=True)
	rooms = db.relationship('Rooms',backref='flats',lazy=True)


class Residents(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	username = db.Column(db.String(100),nullable=False)
	name = db.Column(db.String(100),nullable=False)
	surname = db.Column(db.String(100),nullable=False)
	birthDate = db.Column(db.DateTime,default=None)
	email = db.Column(db.String(100),nullable=False)
	password = db.Column(db.String(100),nullable=False)
	phoneNumber = db.Column(db.String(100),nullable=False)
	passportCode = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(500),nullable=False)
	description = db.Column(db.String(500))
	flatId = db.Column(db.Integer,db.ForeignKey("flats.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("resident_types.id"))
	dateAdded = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
	rfidTags = db.relationship('RfidTags',backref='residents',lazy=True)


class RfidTags(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	residentId = db.Column(db.Integer,db.ForeignKey("residents.id"))
	description = db.Column(db.String(500))


class Rooms(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	flatId = db.Column(db.Integer,db.ForeignKey("flats.id"))
	description = db.Column(db.String(500))
	devices = db.relationship('Devices',backref='rooms',lazy=True)


class Devices(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	ip = db.Column(db.String(100))
	device_key = db.Column(db.String(500),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	state = db.Column(db.Integer,nullable=False,default=0)
	description = db.Column(db.String(500))
	typeId = db.Column(db.Integer,db.ForeignKey("device_types.id"))
	flatId = db.Column(db.Integer,db.ForeignKey("flats.id"))
	roomId = db.Column(db.Integer,db.ForeignKey("rooms.id"))
	dateAdded = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
	pins = db.relationship('Pins',backref='devices',lazy='joined')
	sensors = db.relationship('Sensors',backref='devices',lazy='joined')


class Pins(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	action = db.Column(db.String(500))
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))


class Triggers(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	state = db.Column(db.String(500))


class Sensors(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	value = db.Column(db.Float,default=0.0)
	typeId = db.Column(db.Integer,db.ForeignKey("sensor_types.id"))
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))


class Sensor_records(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	value = db.Column(db.Float,default=0.0)
	date = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))
	sensorId = db.Column(db.Integer,db.ForeignKey("sensors.id"))


class Device_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	devices = db.relationship('Devices',backref='device_types',lazy=True)


class Sensor_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	sensors = db.relationship('Sensors',backref='sensor_types',lazy=True)


class City_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	city = db.relationship('City',backref='city_types',lazy=True)


class Region_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	regions = db.relationship('Regions',backref='region_types',lazy=True)


class House_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	houses = db.relationship('Houses',backref='house_types',lazy=True)


class Flat_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	flats = db.relationship('Flats',backref='flat_types',lazy=True)


class Resident_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	residents = db.relationship('Residents',backref='resident_types',lazy=True)


@app.route("/<deviceName>/<action>")
def action(deviceName, action):
	# example /room1sw/ON
	task=(deviceName+action)
	task_encode=task.encode()
	print(task)
	ser = serial.Serial(arduinoSerialPort)
	ser.baudrate = 9600
	ser.write(task_encode)
	print(task_encode)
	time.sleep(1)
	ser.close()



db.drop_all()
db.create_all()

for room in rooms:
	db_room = Rooms(**room)
	db.session.add(db_room)

for device in devices:
	db_device = Devices(**device)
	db.session.add(db_device)

for pin in pins:
	db_pin = Pins(**pin)
	db.session.add(db_pin)

for sensor in sensors:
	db_sensor = Sensors(**sensor)
	db.session.add(db_sensor)

for device_type in device_types:
	db_device_type = Device_types(**device_type)
	db.session.add(db_device_type)

for sensor_type in sensor_types:
	db_sensor_type = Sensor_types(**sensor_type)
	db.session.add(db_sensor_type)

for trigger in triggers:
	db_trigger = Triggers(**trigger)
	db.session.add(db_trigger)

db.session.commit()