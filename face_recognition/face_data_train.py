import os
import numpy as np
import cv2
from PIL import Image

recognizer = cv2.face.LBPHFaceRecognizer_create()
path = "faces_data/"

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
		cv2.imshow("Training data",faceNP)
		cv2.waitKey(10)

	return np.array(IDs), faces

Ids,faces  = getImagesWithID(path)
recognizer.train(faces,Ids)
recognizer.save("trained/trainingdata.yml")
cv2.destroyAllWindows()