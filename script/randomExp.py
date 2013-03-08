import os
import random
import numpy as np

#params : nbColor nbLandmark sym

MAX_NB_COLOR = 2
MAX_NB_LANDMARK = 5
NB_RUN_PER_SETUP = 10
NB_MODEL = 3

SCENE_WIDTH = 800
SCENE_HEIGHT = 600

def createSceneFile(iNbColor, iNbLandmark, bSym, sFilePath):
	oSceneFile = open(sFilePath, 'w')
	oSceneFile.write("%d %d\n"%(SCENE_WIDTH, SCENE_HEIGHT))
	oSceneFile.write("%d %d\n"%(random.randint(0, SCENE_WIDTH - 1), random.randint(0, SCENE_HEIGHT - 1)))
	for i in range(iNbLandmark):
		oSceneFile.write("%d %d %d\n"%(random.randint(1, iNbColor), random.randint(0, SCENE_WIDTH - 1),
			random.randint(0, SCENE_HEIGHT - 1)))

print os.getcwd()
sDirName = "results"
if not os.path.exists(sDirName):
	os.makedirs(sDirName)

#for bSym in [False, True]:
for bSym in [False]:
	sSymPath = os.path.join(sDirName, "sym=" + str(bSym))
	if not os.path.exists(sSymPath):
		os.makedirs(sSymPath)

	for iNbColor in range(1, MAX_NB_COLOR + 1):
		sColorPath = os.path.join(sSymPath, "nbColor=" + str(iNbColor))
		if not os.path.exists(sColorPath):
			os.makedirs(sColorPath)

		for iNbLandmark in range(1, MAX_NB_LANDMARK + 1):
			sLandmarkPath = os.path.join(sColorPath, "nbLandmark=" + str(iNbLandmark))
			if not os.path.exists(sLandmarkPath):
				os.makedirs(sLandmarkPath)
			
			for iRun in range(NB_RUN_PER_SETUP):
				print bSym, iNbColor, iNbLandmark, iRun
				sSceneFilePath = "%s/run%d.as"%(sLandmarkPath, iRun)
				createSceneFile(iNbColor, iNbLandmark, bSym, sSceneFilePath)
				for iModel in range(NB_MODEL):
					sImageFilePath = "%s/run%d_model%d.tga"%(sLandmarkPath, iRun, iModel)
					if (not os.path.isfile(sImageFilePath)):
						oResFile = open(sDirName + "/res.txt", "a")
						oResFile.write("%d %d %d %d %d "%(bSym, iNbColor, iNbLandmark, iRun, iModel))
						oResFile.close()
						os.system("./animat_exp %s %d %s results/res.txt > /dev/null"%(sSceneFilePath, iModel, sImageFilePath))


# mRes = np.zeros((NB_MODEL, 1, iNbColor, iNbLandmark))
# oResFile = open(sDirName + "/res.txt", "a")
# for sLine in oResFile:
# 	lLine = sLine.split()
# 	mRes[lLine[]]

