from main.models import (
	City,
	Regions,
	Houses,
	Flats,
	Residents,
)

def get_locale_data(tag = ''):
	data = {
		"error": [],
		"message": "Not found",
		"type": "error"
	}
	if not tag:
		regions = Regions.query.all()
		houses = Houses.query.all()
		flats = Flats.query.all()
		residents = Residents.query.all()

		data = {
			"regions": [region.json() for region in regions],
			"houses": [house.json() for house in houses],
			"flats": [flat.json() for flat in flats],
			"residents": [resident.json() for resident in residents],
			"message": "All locale datas",
			"type": "all"
		}

	elif tag:
		if tag == 'regions':
			tag_datas = Regions.query.all()
		if tag == 'houses':
			tag_datas = Houses.query.all()
		if tag == 'flats':
			tag_datas = Flats.query.all()
		if tag == 'residents':
			tag_datas = Residents.query.all()

		data = {
			tag: [tag_data.json() for tag_data in tag_datas],
			"message": f"Data of {tag}",
			"type": tag
		}

	return data