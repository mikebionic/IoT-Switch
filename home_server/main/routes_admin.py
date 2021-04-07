from flask import (
	Flask,
	render_template,
	url_for,
	flash,
	redirect,
	request
)
from main import app
from main import db

@app.route("/admin")
def dashboard():
	return render_template("admin/dashboard.html")