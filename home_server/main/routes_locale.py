from flask import (
	Flask,
	render_template,
	url_for,
	flash,
	redirect,
	request,
	Response,
	jsonify,
	make_response)
import time, requests
from datetime import date, datetime

from main import app
from main import db

from .models import (
	City,
	Region,
	House,
	Flat,
	Resident,
	Room)


@app.route("/city/")
def city_api():
	cities = City.query.all()
	city_data = []
	for city in cities:
		info = city.json()
		regions = [region.json() for region in city.regions]
		info['regions'] = regions
		city_data.append(info)
	return make_response(jsonify(city_data),200)


@app.route("/regions/")
def regions_api():
	regions = Region.query.all()
	regions_data = []
	for region in regions:
		info = region.json()
		houses = [house.json() for house in region.houses]
		info['houses'] = houses
		regions_data.append(info)
	return make_response(jsonify(regions_data),200)


@app.route("/houses/")
def houses_api():
	houses = House.query.all()
	houses_data = []
	for house in houses:
		info = house.json()
		flats = [flat.json() for flat in house.flats]
		info['flats'] = flats
		houses_data.append(info)
	return make_response(jsonify(houses_data),200)


@app.route("/residents/")
def residents_api():
	residents = Resident.query.all()
	residents_data = []
	for resident in residents:
		info = resident.json()
		rfidTags = [rfidTag.json() for rfidTag in resident.rfidTags]
		info['rfidTags'] = rfidTags
		residents_data.append(info)
	return make_response(jsonify(residents_data),200)


@app.route("/rooms/")
def rooms_api():
	rooms = Room.query.all()
	rooms_data = []
	for room in rooms:
		info = room.json()
		devices = [device.json() for device in room.devices]
		info['devices'] = devices
		rooms_data.append(info)
	return make_response(jsonify(rooms_data),200)