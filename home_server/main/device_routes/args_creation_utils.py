def create_pending_arguments_from_device(device):
	pending_arguments = {}
	for pin in device.pins:
		pending_arguments[pin.command] = pin.action
	
	return pending_arguments


def create_argumented_url(pending_arguments):
	argumented_url = ""
	for key, value in pending_arguments.items():
		argumented_url += "{}={}&".format(key, value)

	return argumented_url


def create_separated_device_typeId4_argumented_url_list(device):
	argumented_url_list = []
	for pin in device.pins:
		current_arg = {}
		current_arg["command"] = pin.command
		current_arg["action"] = pin.action
		current_arg["process_key"] = pin.process_key
		current_arg[pin.command] = pin.action
		argumented_url_list.append(current_arg)

	return argumented_url_list

