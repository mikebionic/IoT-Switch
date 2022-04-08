from flask import (
	render_template,
	redirect,
	request,
	flash,
)
from random import randint
from datetime import datetime, timedelta

from flask.helpers import url_for

from main import app, db
from main.models import Resident, QR_code

from flask_login import (
	login_user,
	current_user,
	logout_user,
)


@app.route('/login', methods=["GET", "POST"])
def login():
	if request.method == 'GET':
		if current_user.is_authenticated:
			if current_user.typeId == 1:
				return redirect("/admin")
		return render_template ("admin/login.html")

	if request.method == 'POST':
		username = request.form.get("username")
		password = request.form.get("password")
		try:
			user = Resident.query.filter_by(username = username).first()
			if user:
				if(user and user.password==password):
					login_user(user)
					next_page = request.args.get('next')
					if user.typeId == 1:
						return redirect(next_page) if next_page else redirect("/admin")
					else:
						return redirect(next_page) if next_page else redirect("/resident")
				else:
					raise Exception
			else:
				raise Exception				
		except Exception as ex:
			flash(f'Login ýalňyşlygy, ulanyjy ady ya-da açarsöz ýalnyş!','danger')
			print(ex)
	return render_template ("admin/login.html")


@app.route("/logout")
def logout():
	logout_user()
	return redirect(url_for("login"))