class Config:
	FLASK_ENV = 'development'
	TESTING = True
	SECRET_KEY = "somecrappysecretKey"
	AUTH_TOKEN_EXP_TIME_MINUTES = 40

	# Database
	SQLALCHEMY_DATABASE_URI = "sqlite:///SmartSwitches.db"
	SERVER_URL = "http://127.0.0.1:5000"
	MASTER_ARDUINO_IP = "127.0.0.1"
	SOUND_PLAYER = "playsound"