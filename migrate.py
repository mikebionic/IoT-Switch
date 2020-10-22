from flask import Flask
from flask_sqlalchemy import SQLAlchemy

from datetime import date,datetime,time
from devices_config import devices, device_types, pins

app = Flask (__name__)
app.config['SECRET_KEY'] = "bdbgbn08Vtc4UV$bon(*0pnibuoyvtcr4R"
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///SmartSwitches.db'

db = SQLAlchemy(app)


class Devices(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	ip = db.Column(db.String(100))
	device_key = db.Column(db.String(500),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	state = db.Column(db.Integer,nullable=False,default=0)
	description = db.Column(db.String(500))
	typeId = db.Column(db.Integer,db.ForeignKey("device_types.id"))
	date_added = db.Column(db.DateTime,nullable=False,default=datetime.utcnow)
	pins = db.relationship('Pins',backref='devices',lazy='joined')


class Pins(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	command = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	action = db.Column(db.String(500),default="")
	deviceId = db.Column(db.Integer,db.ForeignKey("devices.id"))


class Device_types(db.Model):
	id = db.Column(db.Integer,primary_key=True)
	name = db.Column(db.String(100),nullable=False)
	description = db.Column(db.String(500))
	devices = db.relationship('Devices',backref='device_types',lazy=True)

db.drop_all()
db.create_all()

for device in devices:
	db_device = Devices(**device)
	db.session.add(db_device)

for pin in pins:
	db_pin = Pins(**pin)
	db.session.add(db_pin)

for device_type in device_types:
	db_device_type = Device_types(**device_type)
	db.session.add(db_device_type)

db.session.commit()