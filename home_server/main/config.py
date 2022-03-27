class Config:
	FLASK_ENV = 'development'
	TESTING = True
	SECRET_KEY = "somecrappysecretKey"
	AUTH_TOKEN_EXP_TIME_MINUTES = 40

	# Database
	SQLALCHEMY_DATABASE_URI = "sqlite:///SmartSwitches.db"
	SQLALCHEMY_ECHO = 1
	SERVER_URL = "http://127.0.0.1:5000"
	MASTER_ARDUINO_IP = "127.0.0.1"

	SYSTEM_IP = "192.168.1.252"
	SYSTEM_MASTER_IP = "192.168.1.254"
	FLAT_SECRET_KEY = "flat1_secret_key_hash"

	SOUND_PLAYER = "playsound"