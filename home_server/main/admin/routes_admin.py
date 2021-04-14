from flask import (
	Flask,
	render_template,
	url_for,
	flash,
	redirect,
	request
)
from main import app
from main.admin.utils.get_locale_data import get_locale_data

@app.route("/admin")
def dashboard():
	data = get_locale_data()
	return render_template("admin/dashboard.html", data)