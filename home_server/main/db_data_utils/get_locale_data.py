from main.models import (
	City,
	Region,
	House,
	Flat,
	Resident,
)

def get_locale_data(tag = ''):
	data = {
		"error": [],
		"message": "Not found",
		"type": "error"
	}
	if not tag:
		regions = Region.query.all()
		houses = House.query.all()
		flats = Flat.query.all()
		residents = Resident.query.all()

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
			tag_datas = Region.query.all()
		if tag == 'houses':
			tag_datas = House.query.all()
		if tag == 'flats':
			tag_datas = Flat.query.all()
		if tag == 'residents':
			tag_datas = Resident.query.all()

		data = {
			tag: [tag_data.json() for tag_data in tag_datas],
			"message": f"Data of {tag}",
			"type": tag
		}

	return data