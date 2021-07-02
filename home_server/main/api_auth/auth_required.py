import jwt
from functools import wraps
from flask import request, jsonify

from main.models import Resident
from main.config import Config


def auth_required(f):
	@wraps(f)
	def decorated(*args,**kwargs):
		token = None
		current_user = None

		if 'auth-token' in request.headers:
			token = request.headers['auth-token']

		if not token:
			return jsonify({"info": "auth-token is missing!"}), 401

		try:
			data = jwt.decode(token, Config.SECRET_KEY, algorithms="HS256")

			# if "id" in data:
			# 	current_user = Resident.query\
			# 		.filter_by(id = data['id'])\
			# 		.first()

			if "secret_key" in data:
				current_user = Resident.query\
					.filter_by(secret_key = data['secret_key'])\
					.first()

			if not current_user:
				raise Exception

		except Exception as ex:
			print(ex)
			return jsonify({"info": "auth-token is invalid!"}), 401

		return f(current_user,*args,**kwargs)

	return decorated
