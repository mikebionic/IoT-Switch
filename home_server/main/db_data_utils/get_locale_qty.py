from main.models import (
	City,
	Regions,
	Houses,
	Flats,
	Residents,
)

def get_locale_qty():
	regions = Regions.query.count()
	houses = Houses.query.count()
	flats = Flats.query.count()
	residents = Residents.query.count()

	data = {
		"regions_qty": regions,
		"houses_qty": houses,
		"flats_qty": flats,
		"residents_qty": residents,
	}
	return data