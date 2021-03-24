class Config:
	FLASK_ENV = 'development'
	TESTING = True
	SECRET_KEY = "somecrappysecretKey"

	# Database
	SQLALCHEMY_DATABASE_URI = "sqlite:///SmartSwitches.db"
	SERVER_URL = "http://127.0.0.1:5000"
	MASTER_ARDUINO_IP = "127.0.0.1"