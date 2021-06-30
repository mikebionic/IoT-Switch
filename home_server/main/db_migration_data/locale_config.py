cities = [
	{
		"id": 1,
		"name": "Ashgabat",
		"secret_key": "ashgabat_city",
		"description": "A capital of turkmenistan",
		# "typeId": 1
	}
]


regions = [
	{
		"id": 1,
		"name": "Koshi",
		"secret_key": "region_koshi",
		"description": "Region on the west side of Ashgabat",
		"cityId": 1,
		# "typeId": 1
	}
]

houses = [
	{
		"house_key": 1,
		"name": "gorjaw jay 1",
		"regionId": 1
	}
]

flats = [
	{
		"flat_key": 1,
		"name": "Default flat",
		"secret_key": "secret_key_hash",
		"description": "Default testing flat",
		"house_key": 1,
		# "houseId": 1,
		# "typeId": 1,
	}
]

rooms = [
	{
		"room_key": 1,
		"name": "Office",
		"flat_key": 1,
		"description": "Room for office work"
	}
]