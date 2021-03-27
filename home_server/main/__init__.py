from flask import Flask
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)
app.config.from_object('config.Config')
db = SQLAlchemy(app)

from . import models
from . import routes_devices
from . import routes_locale
from . import routes_netscan
# from . import routes_serial