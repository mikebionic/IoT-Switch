from flask import jsonify

from .Blockchain import Blockchain
from main import app

blockchain = Blockchain()

@app.route('/navigation', methods=['GET'])
def welcome():
	wl = '''
		<html>
		<head><title>Navigation</title></head>
		<body>
		Navigation
		<br>
		<br>
			<ul>
			<li>For Mining Blocks Visit : <a href="http://127.0.0.1:5000/mineblock">http://127.0.0.1:5000/mineblock</a></li>
			<li>For Viewing the Blockchain Visit : <a href="http://127.0.0.1:5000/getchain">http://127.0.0.1:5000/getchain</a></li>
			<li>For Validating Blockchain Visit : <a href="http://127.0.0.1:5000/validate">http://127.0.0.1:5000/validate</a></li>
			</ul>
		</body>
		</html>
		'''
	return wl

@app.route('/mineblock', methods=['GET'])
def mineblock():
	prevblock = blockchain.getprevblock()
	prevproof = prevblock['proof']
	proof = blockchain.proofofwork(prevproof)
	prevhash = blockchain.hash(prevblock)
	block = blockchain.createblock(proof, prevhash)
	response = {'message': "Block successfully mined!",
				'index': block['index'],
				'timestamp': block['timestamp'],
				'proof': block['proof'],
				'prevhash': block['prevhash']}
	return jsonify(response), 200

@app.route('/getchain', methods=['GET'])
def getchain():
	response = {'chain': blockchain.chain,
				'len': len(blockchain.chain)}
	return jsonify(response), 200

@app.route('/validate', methods=['GET'])
def validate():
	if blockchain.ischainvalid(blockchain.chain):
		response = {'message': "The Blockchain is Valid"}
	else:
		response = {'message': "The Blockchain is Invalid"}
	return jsonify(response), 200