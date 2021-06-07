from datetime import datetime

from main import db

def merge_and_commit(db_entity, payload):
	payload["id"] = None
	payload["dateAdded"] = db_entity.dateAdded
	payload["dateUpdated"] = datetime.now()
	db_entity.do_update(**payload)
	db.session.commit()
	print("make request with updates")
	return db_entity
	# do request here()