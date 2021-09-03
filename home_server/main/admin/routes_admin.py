from flask import (
	Flask,
	render_template,
	url_for,
	flash,
	redirect,
	request
)

from flask_login import (
	current_user,
	login_required
)

from main import app
from main.db_data_utils.get_locale_data import get_locale_data
from main.db_data_utils.get_locale_qty import get_locale_qty
from main.db_data_utils.get_sensors_data import get_sensors_data
from main.db_data_utils.get_devices_data import get_devices_data


@app.route("/admin")
@app.route("/admin/dashboard")
@login_required
def dashboard():
	data = get_locale_qty()
	return render_template(
		"admin/dashboard.html",
		data = data
	)

@app.route("/admin/locale_details")
@login_required
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
@login_required
def residents_table():
	data = get_locale_data("residents")
	return render_template(
		"admin/residents_table.html",
		data = data
	)

@app.route("/admin/sensors_table")
@login_required
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
@login_required
def qr_gen():
	return render_template(
		"admin/qr_gen.html"
	)

	
@app.route("/admin/devices_info")
@login_required
def devices_info():

	data = get_devices_data()
	if not data:
		return redirect(url_for('dashboard'))

	return render_template(
		"admin/devices_info.html",
		data = data
	)