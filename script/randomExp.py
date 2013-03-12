import os
import random
import numpy as np
import matplotlib.pyplot as plt

#params : nbColor nbLandmark sym

MAX_NB_COLOR = 3
MAX_NB_LANDMARK = 5
NB_RUN_PER_SETUP = 10
NB_MODEL = 3
SYM = ["none", "partial", "full"]

SCENE_WIDTH = 800
SCENE_HEIGHT = 600

def createSceneFile(iNbColor, iNbLandmark, sSym, sFilePath):
	oSceneFile = open(sFilePath, 'w')
	# size map
	oSceneFile.write("%d %d\n"%(SCENE_WIDTH, SCENE_HEIGHT))
	if sSym == "none":
		# goal
		oSceneFile.write("%d %d\n"%(random.randint(0, SCENE_WIDTH / 10 - 1), random.randint(0, SCENE_HEIGHT - 1)))
		for i in range(iNbLandmark):
			# landmark
			oSceneFile.write("%d %d %d\n"%(random.randint(1, iNbColor), random.randint(0, SCENE_WIDTH - 1),
				random.randint(0, SCENE_HEIGHT - 1)))
	else:
		if sSym == "partial":
			# goal
			oSceneFile.write("%d %d\n"%(random.randint(0, SCENE_WIDTH / 10 - 1), random.randint(0, SCENE_HEIGHT - 1)))
		else:
			# goal
			oSceneFile.write("%d %d\n"%(random.randint(0, SCENE_WIDTH  / 10 - 1), SCENE_HEIGHT / 2))		
		for i in range(iNbLandmark / 2):
			iColor = random.randint(1, iNbColor)
			fX = random.randint(0, SCENE_WIDTH - 1)
			fY = random.randint(0, SCENE_HEIGHT / 2 - 1)
			# landmark
			oSceneFile.write("%d %d %d\n"%(iColor, fX, fY))
			oSceneFile.write("%d %d %d\n"%(iColor, fX, fY + SCENE_HEIGHT / 2))
		if iNbLandmark % 2 == 1:
			# landmark
			oSceneFile.write("%d %d %d\n"%(random.randint(1, iNbColor), random.randint(0, SCENE_WIDTH - 1),
				SCENE_HEIGHT / 2))

def drawRes(mSubRes, oAx):
	res = oAx.imshow(mSubRes, cmap=plt.cm.jet, interpolation='nearest', vmin=0, vmax=0.5)

	width = len(mSubRes)
	height = len(mSubRes[0])

	for x in xrange(width):
  	  for y in xrange(height):
    	    oAx.annotate("{0:.2f}".format(mSubRes[x][y]), xy=(y, x), 
												horizontalalignment='center',
												verticalalignment='center')

	alphabet = '123456789'
	plt.yticks(range(width), alphabet[:width])
	plt.xticks(range(height), alphabet[:height])

print os.getcwd()
sDirName = "results_exp_sym"
if not os.path.exists(sDirName):
	os.makedirs(sDirName)

for sSym in SYM:
	sSymPath = os.path.join(sDirName, "sym_" + sSym)
	if not os.path.exists(sSymPath):
		os.makedirs(sSymPath)

	for iNbColor in range(1, MAX_NB_COLOR + 1):
		sColorPath = os.path.join(sSymPath, "nbColor_" + str(iNbColor))
		if not os.path.exists(sColorPath):
			os.makedirs(sColorPath)

		for iNbLandmark in range(1, MAX_NB_LANDMARK + 1):
			sLandmarkPath = os.path.join(sColorPath, "nbLandmark_" + str(iNbLandmark))
			if not os.path.exists(sLandmarkPath):
				os.makedirs(sLandmarkPath)
			
			for iRun in range(NB_RUN_PER_SETUP):
				print sSym, iNbColor, iNbLandmark, iRun
				sSceneFilePath = "%s/run%d.as"%(sLandmarkPath, iRun)
				if not os.path.isfile(sSceneFilePath):
					createSceneFile(iNbColor, iNbLandmark, sSym, sSceneFilePath)
				for iModel in range(NB_MODEL):
					sImageFilePathTGA = "%s/run%d_model%d.tga"%(sLandmarkPath, iRun, iModel)
					sImageFilePathPNG = "%s/run%d_model%d.png"%(sLandmarkPath, iRun, iModel)
					if not os.path.isfile(sImageFilePathTGA) and not os.path.isfile(sImageFilePathPNG):
						oResFile = open(sDirName + "/res.txt", "a")
						oResFile.write("%s %d %d %d %d "%(sSym, iNbColor, iNbLandmark, iRun, iModel))
						oResFile.close()
						os.system("./animat_exp %s %d %s results/res.txt > /dev/null"%(sSceneFilePath, iModel + 1, sImageFilePathTGA))
					if not os.path.isfile(sImageFilePathPNG):
						if os.system("convert %s %s"%(sImageFilePathTGA, sImageFilePathPNG)) == 0:
							os.remove(sImageFilePathTGA)



mRes = np.zeros((NB_MODEL, len(SYM), MAX_NB_COLOR, MAX_NB_LANDMARK, NB_RUN_PER_SETUP))
oResFile = open(sDirName + "/res.txt", "r")
for sLine in oResFile:
	lLine = sLine.split()
	lLine[0] = SYM.index(lLine[0])
	lLine = [float(f) for f in lLine]
	mRes[lLine[4], lLine[0], lLine[1] - 1, lLine[2] - 1, lLine[3]] += lLine[5]

mRes = np.mean(mRes, axis=4)

fig = plt.figure()
plt.clf()

drawRes(mRes[0, 0, :, :], fig.add_subplot(331))
drawRes(mRes[1, 0, :, :], fig.add_subplot(332))
drawRes(mRes[2, 0, :, :], fig.add_subplot(333))
drawRes(mRes[0, 1, :, :], fig.add_subplot(334))
drawRes(mRes[1, 1, :, :], fig.add_subplot(335))
drawRes(mRes[2, 1, :, :], fig.add_subplot(336))
drawRes(mRes[0, 2, :, :], fig.add_subplot(337))
drawRes(mRes[1, 2, :, :], fig.add_subplot(338))
drawRes(mRes[2, 2, :, :], fig.add_subplot(339))

# cax = fig.add_axes([0.9, 0.1, 0.03, 0.8])
# fig.colorbar(im, cax=cax)

plt.show()
