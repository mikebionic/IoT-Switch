from flask import (
	render_template,
	redirect,
	request,
	flash,
)
from random import randint
from datetime import datetime, timedelta

from main import app, db
from main.models import Residents, QR_codes

from flask_login import (
	login_user,
	current_user,
	logout_user,
	login_required)


@app.route('/admin/login', methods=["GET", "POST"])
def admin_login():
	if request.method == 'GET':
		if current_user.is_authenticated:
			return redirect("/admin")
		return render_template ("admin/login.html")

	if request.method == 'POST':
		username = request.form.get("username")
		password = request.form.get("password")
		try:
			user = Residents.query.filter_by(username = username).first()
			if user:
				if(user and user.password==password):
					login_user(user)
					next_page = request.args.get('next')
					return redirect(next_page) if next_page else redirect("/admin")
				else:
					raise Exception
			else:
				raise Exception				
		except Exception as ex:
			flash(f'Login ýalňyşlygy, ulanyjy ady ya-da açarsöz ýalnyş!','danger')
			print(ex)
	return render_template ("admin/login.html")


@app.route("/admin/logout")
def admin_logout():
	logout_user()
	return redirect ("/")