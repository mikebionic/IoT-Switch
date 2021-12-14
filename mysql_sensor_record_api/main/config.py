class Config:
	FLASK_ENV = 'development'
	TESTING = True
	SECRET_KEY = "jfvi3orfjklfgvfgbvfgbvghnkgfgdfdsedsfgbh"
	# Database
	SQLALCHEMY_DATABASE_URI = "mysql://bbs:@192.168.1.240/parnik"
	SQLALCHEMY_ECHO = True