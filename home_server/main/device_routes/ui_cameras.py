from flask import (
	render_template,
)

from main import app

from main.models import (
	Device,
)


@app.route("/ui_cameras/",methods=['GET'])
def ui_cameras():
	cam_devices = Device.query.filter_by(typeId = 5).all()
	cameras_list = [cam.json() for cam in cam_devices]
	return render_template(
		"api/ui_cameras.html",
		cameras_list = cameras_list
	)