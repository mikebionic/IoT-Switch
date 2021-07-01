from datetime import date,datetime,time
from flask_login import UserMixin

from main import login_manager
from main import db
from main.core_utils.random_gen import random_gen

@login_manager.user_loader
def load_user(id):
	return Resident.query.get(int(id))


class City(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen())
	description = db.Column(db.String(500))
	typeId = db.Column(db.Integer,db.ForeignKey("city_type.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	regions = db.relationship('Region',backref='city',lazy=True)

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


class Region(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen())
	description = db.Column(db.String(500))
	cityId = db.Column(db.Integer,db.ForeignKey("city.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("region_type.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	houses = db.relationship('House',backref='region',lazy=True)

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


class House(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	house_key = db.Column(db.String)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen())
	description = db.Column(db.String(500))
	longit = db.Column(db.String(100))
	latit = db.Column(db.String(100))
	regionId = db.Column(db.Integer,db.ForeignKey("region.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("house_type.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	flats = db.relationship('Flat',backref='house',lazy=True)

	def json(self):
		houses = {
			"id": self.id,
			"house_key": self.house_key,
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


class Flat(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	flat_key = db.Column(db.String)
	house_key = db.Column(db.String)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen())
	description = db.Column(db.String(500))
	houseId = db.Column(db.Integer,db.ForeignKey("house.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("flat_type.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	residents = db.relationship('Resident',backref='flat',lazy=True)
	devices = db.relationship('Device',backref='flat',lazy=True)
	master_devices = db.relationship('Master_device',backref='flat',lazy=True)
	rooms = db.relationship('Room',backref='flat',lazy=True)

	def json(self):
		flats = {
			"id": self.id,
			"flat_key": self.flat_key,
			"name": self.name,
			"secret_key": self.secret_key,
			"description": self.description,
			"houseId": self.houseId,
			"typeId": self.typeId,
			"dateAdded": self.dateAdded
		}
		return flats


class Resident(db.Model, UserMixin):
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
	flatId = db.Column(db.Integer,db.ForeignKey("flat.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("resident_type.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	rfidTags = db.relationship('RfidTag',backref='resident',lazy=True)

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


class QR_code(db.Model):
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


class RfidTag(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	residentId = db.Column(db.Integer,db.ForeignKey("resident.id"))
	description = db.Column(db.String(500))

	def json(self):
		rfidTags = {
			"id": self.id,
			"name": self.name,
			"residentId": self.residentId,
			"description": self.description
		}
		return rfidTags


class Room(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	room_key = db.Column(db.String)
	flat_key = db.Column(db.String)
	name = db.Column(db.String(100),nullable=False)
	flatId = db.Column(db.Integer,db.ForeignKey("flat.id"))
	description = db.Column(db.String(500))
	devices = db.relationship('Device',backref='room',lazy=True)
	master_devices = db.relationship('Master_device',backref='room',lazy=True)

	def json(self):
		room = {
			"id": self.id,
			"name": self.name,
			"flatId": self.flatId,
			"description": self.description
		}
		return room


class Master_device(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	ip = db.Column(db.String(100))
	barcode = db.Column(db.String(100))
	device_key = db.Column(db.String(1000),nullable=False,default=random_gen(10))
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen(100))
	command = db.Column(db.String(100),default=random_gen(10))
	state = db.Column(db.Integer,default=0)
	description = db.Column(db.String(500))
	typeId = db.Column(db.Integer,db.ForeignKey("device_type.id"))
	flatId = db.Column(db.Integer,db.ForeignKey("flat.id"))
	roomId = db.Column(db.Integer,db.ForeignKey("room.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	pins = db.relationship('Pin',backref='master_device',lazy='joined')
	sensors = db.relationship('Sensor',backref='master_device',lazy='joined')
	sensor_records = db.relationship('Sensor_record',backref='master_device',lazy=True)
	schedules = db.relationship('Schedule',backref='master_device',lazy=True)
	devices = db.relationship('Device',backref='master_device',lazy=True)


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


class Device(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	ip = db.Column(db.String(100))
	barcode = db.Column(db.String(100))
	device_key = db.Column(db.String(1000),nullable=False,default=random_gen(10))
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen(100))
	command = db.Column(db.String(100),default=random_gen(10))
	state = db.Column(db.Integer,default=0)
	description = db.Column(db.String(500))
	master_device_id = db.Column(db.Integer,db.ForeignKey("master_device.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("device_type.id"))
	flatId = db.Column(db.Integer,db.ForeignKey("flat.id"))
	roomId = db.Column(db.Integer,db.ForeignKey("room.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	pins = db.relationship('Pin',backref='device',lazy='joined')
	sensors = db.relationship('Sensor',backref='device',lazy='joined')
	sensor_records = db.relationship('Sensor_record',backref='device',lazy=True)
	schedules = db.relationship('Schedule',backref='device',lazy=True)

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
			"master_device_id": self.master_device_id,
			"typeId": self.typeId,
			"flatId": self.flatId,
			"roomId": self.roomId,
			"dateAdded": self.dateAdded,
			"dateUpdated": self.dateUpdated.timestamp(),
		}
		return device


class Pin(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	process_key = db.Column(db.String(1000),default=random_gen(10))
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen(100))
	description = db.Column(db.String(500))
	action = db.Column(db.String(500))
	master_device_id = db.Column(db.Integer,db.ForeignKey("master_device.id"))
	deviceId = db.Column(db.Integer,db.ForeignKey("device.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	schedules = db.relationship('Schedule',backref='pin',lazy=True)

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
			"master_device_id": self.master_device_id,
			"deviceId": self.deviceId,
			"dateAdded": self.dateAdded,
			"dateUpdated": self.dateUpdated.timestamp(),
		}
		return pin


class Trigger(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	trigger_key = db.Column(db.String)
	name = db.Column(db.String(100),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	state = db.Column(db.String(500))

	def json(self):
		pin = {
			"id": self.id,
			"trigger_key": self.trigger_key,
			"name": self.name,
			"command": self.command,
			"description": self.description,
			"state": self.state
		}
		return pin


class Sensor(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	value = db.Column(db.Float,default=0.0)
	secret_key = db.Column(db.String(1000),nullable=False,default=random_gen(100))
	typeId = db.Column(db.Integer,db.ForeignKey("sensor_type.id"))
	master_device_id = db.Column(db.Integer,db.ForeignKey("master_device.id"))
	deviceId = db.Column(db.Integer,db.ForeignKey("device.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())
	sensor_records = db.relationship('Sensor_record',backref='sensor',lazy=True)
	schedules = db.relationship('Schedule',backref='sensor',lazy=True)

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
			"master_device_id": self.master_device_id,
			"deviceId": self.deviceId,
			"dateAdded": self.dateAdded,
			"dateUpdated": self.dateUpdated.timestamp(),
		}
		return sensor


class Sensor_record(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	value = db.Column(db.Float,default=0.0)
	date = db.Column(db.DateTime,nullable=False,default=datetime.now())
	master_device_id = db.Column(db.Integer,db.ForeignKey("master_device.id"))
	deviceId = db.Column(db.Integer,db.ForeignKey("device.id"))
	sensorId = db.Column(db.Integer,db.ForeignKey("sensor.id"))
	dateAdded = db.Column(db.DateTime,default=datetime.now())
	dateUpdated = db.Column(db.DateTime,default=datetime.now(),onupdate=datetime.now())

	def json(self):
		sensor_records = {
			"id": self.id,
			"name": self.name,
			"description": self.description,
			"value": self.value,
			"date": self.date,
			"master_device_id": self.master_device_id,
			"deviceId": self.deviceId,
			"sensorId": self.sensorId,
			"dateAdded": self.dateAdded,
			"dateUpdated": self.dateUpdated.timestamp(),
		}
		return sensor_records


class Device_type(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	device_type_key = db.Column(db.String)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	devices = db.relationship('Device',backref='device_type',lazy=True)
	master_devices = db.relationship('Master_device',backref='device_type',lazy=True)


	def json(self):
		db_type = {
			"id": self.id,
			"device_type_key": self.device_type_key,
			"name": self.name,
			"description": self.description
		}
		return db_type


class Sensor_type(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	sensor_type_key = db.Column(db.String)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	sensors = db.relationship('Sensor',backref='sensor_type',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"sensor_type_key": self.sensor_type_key,
			"name": self.name,
			"description": self.description
		}
		return db_type


class City_type(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	city = db.relationship('City',backref='city_type',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"name": self.name,
			"description": self.description
		}
		return db_type


class Region_type(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	regions = db.relationship('Region',backref='region_type',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"name": self.name,
			"description": self.description
		}
		return db_type


class House_type(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	houses = db.relationship('House',backref='house_type',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"name": self.name,
			"description": self.description
		}
		return db_type


class Flat_type(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	flats = db.relationship('Flat',backref='flat_type',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"name": self.name,
			"description": self.descriptionnullable
		}
		return db_type


class Resident_type(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	residents = db.relationship('Resident',backref='resident_type',lazy=True)

	def json(self):
		db_type = {
			"id": self.id,
			"name": self.name,
			"description": self.description
		}
		return db_type


class Schedule(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	typeId = db.Column(db.Integer,default=1)
	master_device_id = db.Column(db.Integer,db.ForeignKey("master_device.id"))
	deviceId = db.Column(db.Integer,db.ForeignKey("device.id"))
	pinId = db.Column(db.Integer,db.ForeignKey("pin.id"))
	sensorId = db.Column(db.Integer,db.ForeignKey("sensor.id"))
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
			"master_device_id": self.master_device_id,
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