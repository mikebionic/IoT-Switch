from main import db

from main.models import (
	Devices,
	Sensors,
	Residents,
	City,
	Regions,
	Flats,
	Houses,
	Pins,
	Device_types,
	Sensor_types,
	Triggers,
	QR_codes,
	Rooms,
	Schedules,
)

from main.db_migration_data.devices_config import devices, pins, sensors
from main.db_migration_data.default_devices_config import device_types, sensor_types, triggers
from main.db_migration_data.locale_config import cities, regions, houses, flats, rooms
from main.db_migration_data.residents_config import residents, qr_codes
from main.db_migration_data.schedules_config import schedules


db.drop_all()
db.create_all()

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


for city in cities:
	db_city = City(**city)
	db.session.add(db_city)

for region in regions:
	db_region = Regions(**region)
	db.session.add(db_region)

for house in houses:
	db_house = Houses(**house)
	db.session.add(db_house)

for flat in flats:
	db_flat = Flats(**flat)
	db.session.add(db_flat)

for resident in residents:
	db_resident = Residents(**resident)
	db.session.add(db_resident)

for qr_code in qr_codes:
	db_qr_code = QR_codes(**qr_code)
	db.session.add(db_qr_code)

for room in rooms:
	db_room = Rooms(**room)
	db.session.add(db_room)

for schedule in schedules:
	db_schedule = Schedules(**schedule)
	db.session.add(db_schedule)

db.session.commit()