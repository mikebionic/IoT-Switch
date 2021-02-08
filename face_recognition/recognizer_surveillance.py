import os
import numpy as np
import cv2
from PIL import Image
from pynput.keyboard import Key, Listener

# global command

face_cascade = cv2.CascadeClassifier('../haarcascade_frontalface_default.xml')
cap = cv2.VideoCapture(0)


user_data = [
	{
		"id": 1,
		"name": "Mike"
	}
]


def record_new_face():
	id = input('enter user id')
	sampleN=0;

	while (command == "1"):
		ret, img = cap.read()
		gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

		faces = face_cascade.detectMultiScale(gray, 1.3, 5)

		for (x,y,w,h) in faces:
			sampleN = sampleN + 1;
			cv2.imwrite("facesData/User."+str(id)+ "." +str(sampleN)+ ".jpg", gray[y:y+h, x:x+w])
			cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
			cv2.waitKey(100)

		cv2.imshow('img',img)
		cv2.waitKey(1)
		if sampleN > 20:
			break

	cap.release()
	cv2.destroyAllWindows()
	# global command
	# command == "3"




def update_trained_data():
	recognizer = cv2.face.LBPHFaceRecognizer_create()
	path = "facesData/"
	def getImagesWithID(path):
		imagePaths = [os.path.join(path, f) for f in os.listdir(path)]
		faces = []
		IDs = []
		for imagePath in imagePaths:
			facesImg = Image.open(imagePath).convert('L')
			faceNP = np.array(facesImg, 'uint8')
			ID = int(os.path.split(imagePath)[-1].split(".")[1])
			faces.append(faceNP)
			IDs.append(ID)
			cv2.imshow("Adding faces for traning",faceNP)
			cv2.waitKey(10)
		return np.array(IDs), faces
	Ids,faces  = getImagesWithID(path)
	recognizer.train(faces,Ids)
	recognizer.save("faceREC/trainingdata.yml")
	cv2.destroyAllWindows()



def recognizer():
	recognizer = cv2.face.LBPHFaceRecognizer_create()
	recognizer.read("faceREC/trainingdata.yml")
	id = 0
	treshold = 45
	font = cv2.FONT_HERSHEY_SIMPLEX
	ret, img = cap.read()

	global command
	while(command == "3"):
		gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
		faces = face_cascade.detectMultiScale(gray, 1.5, 5)

		for (x,y,w,h) in faces:
			cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)

			id, conf = recognizer.predict(gray[y:y+h,x:x+w])

			print(id, conf)

			if (id == 2 and conf<treshold):
				id = "alok"
			if (id == 1 and conf<treshold):
				id = "Mike"
			if (id == 3 and conf<treshold):
				id = "anjali"
			if (id == 4 and conf<treshold):
				id = "Gaurav"
			if (id == 5 and conf<treshold):
				id = 'rahul'
			if (id == 6 and conf<treshold):
				id = "akshay"
			print(id)

			cv2.putText(img,str(id),(x,y+h),font,255,(255, 255, 255))

		cv2.imshow('img',img)
		if cv2.waitKey(1) == ord('q'):
			break

	cap.release()
	cv2.destroyAllWindows()


if __name__ == "__main__":

	def on_press(key):
		global command
		if (str(key) == "'a'"):
			command = "1"
		if (str(key) == "'b'"):
			command = "2"
		if (str(key) == "'c'"):
			command = "3"
		
		print(command)
		if command == "1":
			print("first called")
			record_new_face()
		if command == "2":
			print("second called")
		if command == "3":
			print("third called")
			recognizer()
		# if command == "q":
		# 	break
		# print("Key pressed: {0}".format(key))


	def on_release(key):
		print("Key released: {0}".format(key))
		if key == Key.esc:
			return False

	with Listener(
		on_press=on_press,
		on_release=on_release) as listener:
		listener.join()

	# while True:
