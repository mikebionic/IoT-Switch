from datetime import date,datetime,time
from flask_login import UserMixin

from main import login_manager
from main import db
from main.core_utils.random_gen import random_gen

@login_manager.user_loader
def load_user(id):
	return Residents.query.get(int(id))


class City(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen())
	description = db.Column(db.String(500))
	typeId = db.Column(db.Integer,db.ForeignKey("city_types.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	regions = db.relationship('Regions',backref='city',lazy=True)

	def json(self):
		city = {
			"id": self.id,
			"name": self.name,
			"secret_key": self.secret_key,
			"description": self.description,
			"typeId": self.typeId,
			"dateAdded": self.dateAdded
		}
		return city


class Regions(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen())
	description = db.Column(db.String(500))
	cityId = db.Column(db.Integer,db.ForeignKey("city.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("region_types.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	houses = db.relationship('Houses',backref='regions',lazy=True)

	def json(self):
		regions = {
			"id": self.id,
			"name": self.name,
			"secret_key": self.secret_key,
			"description": self.description,
			"cityId": self.cityId,
			"typeId": self.typeId,
			"dateAdded": self.dateAdded
		}
		return regions


class Houses(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen())
	description = db.Column(db.String(500))
	longit = db.Column(db.String(100))
	latit = db.Column(db.String(100))
	regionId = db.Column(db.Integer,db.ForeignKey("regions.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("house_types.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	flats = db.relationship('Flats',backref='houses',lazy=True)

	def json(self):
		houses = {
			"id": self.id,
			"name": self.name,
			"secret_key": self.secret_key,
			"description": self.description,
			"longit": self.longit,
			"latit": self.latit,
			"regionId": self.regionId,
			"typeId": self.typeId,
			"dateAdded": self.dateAdded
		}
		return houses


class Flats(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen())
	description = db.Column(db.String(500))
	houseId = db.Column(db.Integer,db.ForeignKey("houses.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("flat_types.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	residents = db.relationship('Residents',backref='flats',lazy=True)
	devices = db.relationship('Devices',backref='flats',lazy=True)
	rooms = db.relationship('Rooms',backref='flats',lazy=True)

	def json(self):
		flats = {
			"id": self.id,
			"name": self.name,
			"secret_key": self.secret_key,
			"description": self.description,
			"houseId": self.houseId,
			"typeId": self.typeId,
			"dateAdded": self.dateAdded
		}
		return flats


class Residents(db.Model, UserMixin):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	surname = db.Column(db.String(100))
	birthDate = db.Column(db.DateTime)
	email = db.Column(db.String(100))
	username = db.Column(db.String(100))
	password = db.Column(db.String(100))
	phoneNumber = db.Column(db.String(100))
	passportCode = db.Column(db.String(100))
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen())
	description = db.Column(db.String(500))
	flatId = db.Column(db.Integer,db.ForeignKey("flats.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("resident_types.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	rfidTags = db.relationship('RfidTags',backref='residents',lazy=True)

	def json(self):
		residents = {
			"id": self.id,
			"name": self.name,
			"surname": self.surname,
			"birthDate": self.birthDate,
			"email": self.email,
			"username": self.username,
			"password": self.password,
			"phoneNumber": self.phoneNumber,
			"passportCode": self.passportCode,
			"secret_key": self.secret_key,
			"description": self.description,
			"flatId": self.flatId,
			"typeId": self.typeId,
			"dateAdded": self.dateAdded
		}
		return residents


class QR_codes(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen())
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	registered = db.Column(db.Boolean, default=False)
	typeId = db.Column(db.Integer, default=0)

	def json(self):
		data = {
			"id": self.id,
			"secret_key": self.secret_key,
			"dateAdded": self.dateAdded,
			"registered": self.registered,
			"typeId": self.typeId,
		}
		return data


class RfidTags(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	residentId = db.Column(db.Integer,db.ForeignKey("residents.id"))
	description = db.Column(db.String(500))

	def json(self):
		rfidTags = {
			"id": self.id,
			"name": self.name,
			"residentId": self.residentId,
			"description": self.description
		}
		return rfidTags


class Rooms(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	flatId = db.Column(db.Integer,db.ForeignKey("flats.id"))
	description = db.Column(db.String(500))
	devices = db.relationship('Devices',backref='rooms',lazy=True)

	def json(self):
		room = {
			"id": self.id,
			"name": self.name,
			"flatId": self.flatId,
			"description": self.description
		}
		return room


class Devices(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	ip = db.Column(db.String(100))
	barcode = db.Column(db.String(100))
	device_key = db.Column(db.String(1000),nullable=False,default=random_gen(10))
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen(100))
	command = db.Column(db.String(100),default=random_gen(10))
	state = db.Column(db.Integer,default=0)
	description = db.Column(db.String(500))
	typeId = db.Column(db.Integer,db.ForeignKey("device_types.id"))
	flatId = db.Column(db.Integer,db.ForeignKey("flats.id"))
	roomId = db.Column(db.Integer,db.ForeignKey("rooms.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	pins = db.relationship('Pins',backref='devices',lazy='joined')
	sensors = db.relationship('Sensors',backref='devices',lazy='joined')
	sensor_records = db.relationship('Sensor_records',backref='devices',lazy=True)
	schedules = db.relationship('Schedules',backref='devices',lazy=True)

	def do_update(self, **kwargs):
		for key, value in kwargs.items():
			if value is not None:
				if hasattr(self, key):
					setattr(self, key, value)

	def json(self):
		device = {
			"id": self.id,
			"name": self.name,
			"ip": self.ip,
			"barcode": self.barcode,
			"device_key": self.device_key,
			"secret_key": self.secret_key,
			"command": self.command,
			"state": self.state,
			"description": self.description,
			"typeId": self.typeId,
			"flatId": self.flatId,
			"roomId": self.roomId,
			"dateAdded": self.dateAdded,
			"dateUpdated": self.dateUpdated.timestamp(),
		}
		return device


class Pins(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	process_key = db.Column(db.String(1000),default=random_gen(10))
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen(100))
	description = db.Column(db.String(500))
	action = db.Column(db.String(500))
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	schedules = db.relationship('Schedules',backref='pins',lazy=True)

	def do_update(self, **kwargs):
		for key, value in kwargs.items():
			if value is not None:
				if hasattr(self, key):
					setattr(self, key, value)

	def json(self):
		pin = {
			"id": self.id,
			"name": self.name,
			"command": self.command,
			"process_key": self.process_key,
			"secret_key": self.secret_key,
			"description": self.description,
			"action": self.action,
			"deviceId": self.deviceId,
			"dateAdded": self.dateAdded,
			"dateUpdated": self.dateUpdated.timestamp(),
		}
		return pin


class Triggers(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	state = db.Column(db.String(500))

	def json(self):
		pin = {
			"id": self.id,
			"name": self.name,
			"command": self.command,
			"description": self.description,
			"state": self.state
		}
		return pin


class Sensors(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	value = db.Column(db.Float,default=0.0)
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen(100))
	typeId = db.Column(db.Integer,db.ForeignKey("sensor_types.id"))
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	sensor_records = db.relationship('Sensor_records',backref='sensors',lazy=True)
	schedules = db.relationship('Schedules',backref='sensors',lazy=True)

	def do_update(self, **kwargs):
		for key, value in kwargs.items():
			if value is not None:
				if hasattr(self, key):
					setattr(self, key, value)

	def json(self):
		sensor = {
			"id": self.id,
			"name": self.name,
			"command": self.command,
			"description": self.description,
			"value": self.value,
			"secret_key": self.secret_key,
			"typeId": self.typeId,
			"deviceId": self.deviceId,
			"dateAdded": self.dateAdded,
			"dateUpdated": self.dateUpdated.timestamp(),
		}
		return sensor


class Sensor_records(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	value = db.Column(db.Float,default=0.0)
	date = db.Column(db.DateTime,nullable=False,default=datetime.now())
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))
	sensorId = db.Column(db.Integer,db.ForeignKey("sensors.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())

	def json(self):
		sensor_records = {
			"id": self.id,
			"name": self.name,
			"description": self.description,
			"value": self.value,
			"date": self.date,
			"deviceId": self.deviceId,
			"sensorId": self.sensorId,
			"dateAdded": self.dateAdded,
			"dateUpdated": self.dateUpdated.timestamp(),
		}
		return sensor_records


class Device_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	devices = db.relationship('Devices',backref='device_types',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"name": self.name,
			"description": self.description
		}
		return db_type


class Sensor_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	sensors = db.relationship('Sensors',backref='sensor_types',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"name": self.name,
			"description": self.description
		}
		return db_type


class City_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	city = db.relationship('City',backref='city_types',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"name": self.name,
			"description": self.description
		}
		return db_type


class Region_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	regions = db.relationship('Regions',backref='region_types',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"name": self.name,
			"description": self.description
		}
		return db_type


class House_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	houses = db.relationship('Houses',backref='house_types',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"name": self.name,
			"description": self.description
		}
		return db_type


class Flat_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	flats = db.relationship('Flats',backref='flat_types',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"name": self.name,
			"description": self.descriptionnullable
		}
		return db_type


class Resident_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	residents = db.relationship('Residents',backref='resident_types',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"name": self.name,
			"description": self.description
		}
		return db_type


class Schedules(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	typeId = db.Column(db.Integer,default=1)
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))
	pinId = db.Column(db.Integer,db.ForeignKey("pins.id"))
	sensorId = db.Column(db.Integer,db.ForeignKey("sensors.id"))
	on_action = db.Column(db.String)
	on_state = db.Column(db.Integer)
	on_value = db.Column(db.String)
	on_time = db.Column(db.DateTime)
	device_command = db.Column(db.String)
	pin_action = db.Column(db.String(100))
	description = db.Column(db.String(500))
	path = db.Column(db.String(255))
	url = db.Column(db.String(500),nullable=False,default="/esp/JsonToArg/")
	method = db.Column(db.String(100),default="POST")

	def json(self):
		device = {
			"id": self.id,
			"name": self.name,
			"typeId": self.typeId,
			"deviceId": self.deviceId,
			"pinId": self.pinId,
			"sensorId": self.sensorId,
			"on_action": self.on_action,
			"on_state": self.on_state,
			"on_value": self.on_value,
			"on_time": self.on_time,
			"device_command": self.device_command,
			"pin_action": self.pin_action,
			"description": self.description,
			"path": self.path,
			"url": self.url,
			"method": self.method
		}
		return device