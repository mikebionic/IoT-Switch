from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager

from main.config import Config

app = Flask(__name__)
app.config.from_object(Config)

db = SQLAlchemy(app)
login_manager = LoginManager(app)

login_manager.login_view = 'login'
login_manager.login_message = 'Akylly ulgama girin!'
login_manager.login_message_category = 'info'

from . import models

from .api_auth import *

from . import routes_devices
from . import routes_locale
from . import routes_netscan
from .device_routes import *
from .sensor_routes import *
from .blockchain import *

# from . import routes_serial

from .admin import routes_admin
from .admin import login

from .scheduler import routes_scheduler