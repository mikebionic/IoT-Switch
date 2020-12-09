from flask import (
	Flask,
	render_template,
	url_for,
	flash,
	redirect,
	request,
	Response,
	jsonify,
	make_response)
from flask_sqlalchemy import SQLAlchemy
from flask_socketio import SocketIO, emit 

app = Flask (__name__)

app.config['SECRET_KEY'] = "bdbgbn08Vtc4UV$bon(*0pnibuoyvtcr4R"
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///SmartSwitches.db'
db = SQLAlchemy(app)
socketio = SocketIO(app)


@socketio.on('connect')
def handle_connect():
	emit('connection', {'message': 'successfully connected'}, broadcast=True)


@socketio.on('disconnect')
def handle_disconnect():
	emit('connection', {'message': 'disconnected'}, broadcast=True)


@socketio.on('device_command')
def handle_device_command(json):
	print(f'Received command {str(json)}')


if __name__ == "__main__":
	app.run(host="0.0.0.0" , port=5000 , debug=True)
