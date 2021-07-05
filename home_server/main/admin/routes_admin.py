from flask import (
	Flask,
	render_template,
	url_for,
	flash,
	redirect,
	request
)
from main import app
from main.db_data_utils.get_locale_data import get_locale_data
from main.db_data_utils.get_locale_qty import get_locale_qty
from main.db_data_utils.get_sensors_data import get_sensors_data
from main.db_data_utils.get_devices_data import get_devices_data


@app.route("/admin")
@app.route("/admin/dashboard")
def dashboard():
	data = get_locale_qty()
	return render_template(
		"admin/dashboard.html",
		data = data
	)

@app.route("/admin/locale_details")
def locale_details():
	tag = request.args.get('tag', '', type=str)

	if not tag:
		return redirect(url_for('dashboard'))

	data = get_locale_data(tag)
	if not data:
		return redirect(url_for('dashboard'))

	return render_template(
		"admin/locale_details.html",
		data = data
	)

@app.route("/admin/residents_table")
def residents_table():
	data = get_locale_data("residents")
	return render_template(
		"admin/residents_table.html",
		data = data
	)

@app.route("/admin/sensors_table")
def sensors_table():
	data = get_sensors_data()
	return render_template(
		"admin/sensors_table.html",
		data = data
	)


@app.route("/widgets")
def widgets():
	return render_template(
		"admin/widgets.html"
	)

@app.route("/admin/qr_gen")
def qr_gen():
	return render_template(
		"admin/qr_gen.html"
	)

	