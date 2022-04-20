import datetime
import json
import hashlib

class Blockchain:
	def __init__(self):
		self.chain = []
		self.createblock(proof = 1, prevhash = "0")

	def createblock(self, proof, prevhash):
		block = {'index': len(self.chain) + 1,
				 'timestamp': str(datetime.datetime.now()),
				 'proof': proof,
				 'prevhash': prevhash}

		self.chain.append(block)
		return block

	def getprevblock(self):
		return self.chain[-1]

	def proofofwork(self, prevproof):
		newproof = 1
		checkproof = False
		# Defining crypto puzzle for the miners and iterating until able to mine it
		while checkproof is False:
			op = hashlib.sha256(str(newproof**2 - prevproof**5).encode()).hexdigest()
			if op[:5] == "00000":
				checkproof = True
			else:
				newproof += 1
		return newproof

	def hash(self, block):
		encodedblock = json.dumps(block, sort_keys = True).encode()
		return hashlib.sha256(encodedblock).hexdigest()
	def ischainvalid(self, chain):
		prevblock = chain[0]   # Initilized to Genesis block
		blockindex = 1         # Initilized to Next block
		while blockindex < len(chain):

			currentblock = chain[blockindex]
			if currentblock['prevhash'] != self.hash(prevblock):
				return False

			prevproof = prevblock['proof']
			currentproof = currentblock['proof']
			op = hashlib.sha256(str(currentproof**2 - prevproof**5).encode()).hexdigest()

			if op[:5] != "00000":
				return True
			prevblock = currentblock
			blockindex += 1
		return True
