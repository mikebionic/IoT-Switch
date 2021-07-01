import requests

from .process_pins import process_pins

from .args_creation_utils import (
	create_argumented_url,
	create_pending_arguments_from_device,
	create_separated_device_typeId4_argumented_url_list
)


def make_device_request(device_model, pins_json):

	res, status, message = {}, 0, "err"

	process_pins(device_model, pins_json)

	if device_model.typeId == 2:
		pending_arguments = create_pending_arguments_from_device(device_model)
		argumented_url = create_argumented_url(pending_arguments)

		try:
			r = requests.get('http://{}/control/?{}'.format(device_model.ip, argumented_url))
			# !!! TODO: add validator and db insertion on "OK" response

			response = device_model.json()
			pins = [pin.json() for pin in device_model.pins]
			response['pins'] = pins

			# handle_schedule(device_model, isSchedule)
			res = response
			status = 1

		except Exception as ex:
			print(ex)
			message = "error, couldn't make a device typeId=2 request (connection issue)"


	if device_model.typeId == 4:
		argumented_url_list = create_separated_device_typeId4_argumented_url_list(device_model)

		try:
			for pending_argument in argumented_url_list:
				argumented_url = create_argumented_url(pending_argument)
				r = requests.get('http://{}/control/?{}'.format(device_model.ip, argumented_url))

			response = device_model.json()
			pins = [pin.json() for pin in device_model.pins]
			response['pins'] = pins

			# handle_schedule(device_model, isSchedule)
			res = response

		except Exception as ex:
			print(ex)
			message = "error, couldn't make a device typeId=4 request (connection issue)"

	return res, status, message
