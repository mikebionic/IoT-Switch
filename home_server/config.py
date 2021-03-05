class Config:
	FLASK_ENV = 'development'
	TESTING = True
	SECRET_KEY = "somecrappysecretKey"

	# Database
	SQLALCHEMY_DATABASE_URI = "sqlite:///SmartSwitches.db"
	SERVER_URL = "127.0.0.1:5000"