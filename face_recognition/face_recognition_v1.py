import numpy as np
import cv2
import requests
from time import sleep
from datetime import datetime, timedelta
from trained_users import users
import json

id = 0
delay_seconds = 5
last_time = datetime.now()
treshold = 45
door_server_url = "http://192.168.1.252"

face_cascade = cv2.CascadeClassifier('cascades/haarcascade_frontalface_default.xml')
recognizer = cv2.face.LBPHFaceRecognizer_create()
recognizer.read("trained/trainingdata.yml")

cap = cv2.VideoCapture(0)
font = cv2.FONT_HERSHEY_SIMPLEX


def validate_user(id):
	state = 0

	thisUser = [user for user in users if user["id"] == id]
	thisUser = thisUser[0] if thisUser else None

	if thisUser:
		if thisUser["permission"] != 0:
			print(thisUser["name"])
			state = 1

	return state


def send_request():
	payload = {"command": "unlock_door", "state": 1, "action": ""}
	r = requests.post(
        	"{}{}".format(door_server_url,"/esp/"),
		data = json.dumps(payload),
		headers = {'Content-Type': 'application/json'})

while 1:
	ret, img = cap.read()
	gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	faces = face_cascade.detectMultiScale(gray, 1.5, 5)
	for (x,y,w,h) in faces:
		cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)

		id, conf = recognizer.predict(gray[y:y+h,x:x+w])

		print(id, conf)

		if (conf < treshold):
			if datetime.now() > last_time + timedelta(seconds = delay_seconds):
				if validate_user(id):
					print("validated")
					last_time = datetime.now()
					try:
						send_request()
					except Exception as ex:
						print(ex)
					#sleep(5)
			cv2.putText(img,str(id),(x,y+h),font,255,(255, 255, 255))

	cv2.imshow('img', img)
	if cv2.waitKey(1) == ord('q'):
		break

cap.release()
cv2.destroyAllWindows()
