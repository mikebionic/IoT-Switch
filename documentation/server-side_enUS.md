# Documentation about the server side of the project

The project is based on communication and data collection between devices and server.
Basic schematic is an interconnected network with an access of IoT device and database server.

Programming languages used:
	- C++
	- Python

The aim of the server side app:
	- Creation a bridge between devices
	- Saving the data and states
	- Securing the actions and communication
	- Creation the base API for client-side apps
	- Synch between cloud data and local data

Server-side handles a database with a relation-constructured structured data, and webserver written on Python language, handling all data and working on all main operations of connection, requests handling, data saving, redirecting, securing, hashing of information between devices and client-side applications.

API created and documented to easily create client side applications, for any platforms as Android, iOS, or create web-client on JavaScript. At the same time, webserver API is built for expanding the quantitiy and organizing of IoT devices.

Each device written, has it's own secure key, and "device type" property makes selection of usage type of this device and it's working technique.