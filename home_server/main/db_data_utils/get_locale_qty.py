from main.models import (
	City,
	Region,
	House,
	Flat,
	Resident,
)

def get_locale_qty():
	regions = Region.query.count()
	houses = House.query.count()
	flats = Flat.query.count()
	residents = Resident.query.count()

	data = {
		"regions_qty": regions,
		"houses_qty": houses,
		"flats_qty": flats,
		"residents_qty": residents,
	}
	return data