from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager

app = Flask(__name__)
app.config.from_object('config.Config')
db = SQLAlchemy(app)
login_manager = LoginManager(app)

login_manager.login_view = 'admin.login'
login_manager.login_message = 'Akylly ulgama girin!'
login_manager.login_message_category = 'info'

from . import models
from . import routes_devices
from . import routes_locale
from . import routes_netscan
from .device_routes import esp_json_to_arg
from .login import login
# from . import routes_serial

from .admin import routes_admin
from .admin import login

from .scheduler import routes_scheduler