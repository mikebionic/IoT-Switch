from datetime import date,datetime,time
from main import db


class City(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	secret_key = db.Column(db.String(500),nullable=False)
	description = db.Column(db.String(500))
	typeId = db.Column(db.Integer,db.ForeignKey("city_types.id"))
	dateAdded = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
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
	secret_key = db.Column(db.String(500),nullable=False)
	description = db.Column(db.String(500))
	cityId = db.Column(db.Integer,db.ForeignKey("city.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("region_types.id"))
	dateAdded = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
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
	secret_key = db.Column(db.String(500),nullable=False)
	description = db.Column(db.String(500))
	longit = db.Column(db.String(100))
	latit = db.Column(db.String(100))
	regionId = db.Column(db.Integer,db.ForeignKey("regions.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("house_types.id"))
	dateAdded = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
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
	secret_key = db.Column(db.String(500),nullable=False)
	description = db.Column(db.String(500))
	houseId = db.Column(db.Integer,db.ForeignKey("houses.id"))
	typeId = db.Column(db.Integer,db.ForeignKey("flat_types.id"))
	dateAdded = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
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

	def json(self):
		residents = {
			"id": self.id,
			"username": self.username,
			"name": self.name,
			"surname": self.surname,
			"birthDate": self.birthDate,
			"email": self.email,
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
	sensor_records = db.relationship('Sensor_records',backref='devices',lazy=True)
	schedules = db.relationship('Schedules',backref='devices',lazy=True)

	def json(self):
		device = {
			"id": self.id,
			"name": self.name,
			"ip": self.ip,
			"barcode": self.barcode,
			"device_key": self.device_key,
			"command": self.command,
			"state": self.state,
			"description": self.description,
			"typeId": self.typeId,
			"flatId": self.flatId,
			"roomId": self.roomId,
			"dateAdded": self.dateAdded
		}
		return device


class Pins(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	action = db.Column(db.String(500))
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))
	schedules = db.relationship('Schedules',backref='pins',lazy=True)

	def json(self):
		pin = {
			"id": self.id,
			"name": self.name,
			"command": self.command,
			"description": self.description,
			"action": self.action,
			"deviceId": self.deviceId,
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
	typeId = db.Column(db.Integer,db.ForeignKey("sensor_types.id"))
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))
	sensor_records = db.relationship('Sensor_records',backref='sensors',lazy=True)

	def json(self):
		sensor = {
			"id": self.id,
			"name": self.name,
			"command": self.command,
			"description": self.description,
			"value": self.value,
			"typeId": self.typeId,
			"deviceId": self.deviceId,
		}
		return sensor


class Sensor_records(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	value = db.Column(db.Float,default=0.0)
	date = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))
	sensorId = db.Column(db.Integer,db.ForeignKey("sensors.id"))

	def json(self):
		sensor_records = {
			"id": self.id,
			"name": self.name,
			"description": self.description,
			"value": self.value,
			"date": self.date,
			"deviceId": self.deviceId,
			"sensorId": self.sensorId,
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
			"description": self.description
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


class Schedule(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))
	pinId = db.Column(db.Integer,db.ForeignKey("pins.id"))
	action = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	url = db.Column(db.String(500),nullable=False,default="/esp/JsonToArg/")
	method = db.Column(db.String(100),default="POST")

	def json(self):
		device = {
			"id": self.id,
			"name": self.name,
			"deviceId": self.deviceId,
			"pinId": self.pinId,
			"action": self.action,
			"description": self.description,
			"url": self.url,
			"method": self.method
		}
		return device