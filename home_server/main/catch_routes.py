
from main import app

@app.route('/', defaults={'path': ''})
@app.route('/<path:path>')
def catch_routes(path):
	return 'You want path: %s' % path
