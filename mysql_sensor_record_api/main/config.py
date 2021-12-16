class Config:
	FLASK_ENV = 'development'
	TESTING = True
	SECRET_KEY = "jfvi3orfjklfgvfgbvfgbvghnkgfgdfdsedsfgbh"
	# Database
	
	USE_SMART_RECORD_TYPE = 1
	if USE_SMART_RECORD_TYPE:
		SQLALCHEMY_DATABASE_URI = "sqlite:///sensor_records.db"
	else:
		SQLALCHEMY_DATABASE_URI = "mysql://bbs:@192.168.1.240/parnik"
	SQLALCHEMY_ECHO = True