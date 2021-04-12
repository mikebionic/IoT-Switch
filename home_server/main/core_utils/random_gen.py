import string
import random

def random_gen(length = 1000):
	data = ''.join(random.choices(string.ascii_letters+string.digits,k=length))
	return data