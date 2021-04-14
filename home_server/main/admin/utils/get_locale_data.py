
from main.models import (
	City,
	Regions,
	Houses,
	Flats,
	Residents,
)

def get_locale_data():
	regions = Regions.query.all()
	houses = Houses.query.all()
	flats = Flats.query.all()
	residents = Residents.query.all()

	data = {
		"regions": regions.to_json(),
		"houses": houses.to_json(),
		"flats": flats.to_json(),
		"residents": residents.to_json(),
	}
	return data