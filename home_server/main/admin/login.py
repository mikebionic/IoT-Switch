from flask import (
	render_template,
	redirect,
	request
)
from random import randint
from datetime import datetime, timedelta

from main import app, db
from main.models import Residents, QR_codes


@app.route('/login')
def admin_login():
	return render_template('login/login.html')