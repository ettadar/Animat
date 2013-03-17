import os
import random
import numpy as np
import matplotlib.pyplot as plt

SCENE_WIDTH = 600
SCENE_HEIGHT = 600
NB_COLORS = [1, 2, 3]
NB_LANDMARKS = [1, 2, 3, 4, 5]
NB_RUN_PER_SETUP = 100
MODELS = [1, 2, 3]
SYM = ["none", "partial", "full"]

DIR_NAME = "results/results_exp_sym"




# SCENE_WIDTH = 600
# SCENE_HEIGHT = 600
# NB_COLORS = [1, 2, 3]
# NB_LANDMARKS = [3, 4, 5]
# NB_RUN_PER_SETUP = 100
# MODELS = [1, 2, 3, 4, 5]
# SYM = ["none"]

# DIR_NAME = "results/results_exp_new_models"




# SCENE_WIDTH = 600
# SCENE_HEIGHT = 600
# NB_COLORS = [1, 2, 3]
# NB_LANDMARKS = [3, 4, 5]
# NB_RUN_PER_SETUP = 20
# MODELS = [3, 4, 5]
# SYM = ["none", ...]

# DIR_NAME = "results/results_exp"

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
	res = oAx.imshow(mSubRes, cmap=plt.cm.jet, interpolation='nearest', vmin=0, vmax=1)

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

if not os.path.exists(DIR_NAME):
	os.makedirs(DIR_NAME)

for sSym in SYM:
	sSymPath = os.path.join(DIR_NAME, "sym_" + sSym)
	if not os.path.exists(sSymPath):
		os.makedirs(sSymPath)

	for iNbColor in NB_COLORS:
		sColorPath = os.path.join(sSymPath, "nbColor_" + str(iNbColor))
		if not os.path.exists(sColorPath):
			os.makedirs(sColorPath)

		for iNbLandmark in NB_LANDMARKS:
			sLandmarkPath = os.path.join(sColorPath, "nbLandmark_" + str(iNbLandmark))
			if not os.path.exists(sLandmarkPath):
				os.makedirs(sLandmarkPath)
			
			for iRun in range(NB_RUN_PER_SETUP):
				print sSym, iNbColor, iNbLandmark, iRun
				sSceneFilePath = "%s/run%d.as"%(sLandmarkPath, iRun)
				if not os.path.isfile(sSceneFilePath):
					createSceneFile(iNbColor, iNbLandmark, sSym, sSceneFilePath)

				for iModel in MODELS:
					sImageFilePathTGA = "%s/run%d_model%d.tga"%(sLandmarkPath, iRun, iModel)
					sImageFilePathPNG = "%s/run%d_model%d.png"%(sLandmarkPath, iRun, iModel)
					if not os.path.isfile(sImageFilePathTGA) and not os.path.isfile(sImageFilePathPNG):
						oResFile = open(DIR_NAME + "/res.txt", "a")
						oResFile.write("%s %d %d %d %d "%(sSym, iNbColor, iNbLandmark, iRun, iModel))
						oResFile.close()
						os.system("./animat_exp %s %d %s %s/res.txt > /dev/null"%(sSceneFilePath, iModel, sImageFilePathTGA, DIR_NAME))
					if not os.path.isfile(sImageFilePathPNG):
						if os.system("convert %s %s"%(sImageFilePathTGA, sImageFilePathPNG)) == 0:
							os.remove(sImageFilePathTGA)



mRes = np.zeros((len(MODELS), len(SYM), len(NB_COLORS), len(NB_LANDMARKS), NB_RUN_PER_SETUP))
oResFile = open(DIR_NAME + "/res.txt", "r")
for sLine in oResFile:
	lLine = sLine.split()
	#if len(sLine) == 5:
	if True:
		lLine[0] = SYM.index(lLine[0])
		lLine[1] = NB_COLORS.index(int(lLine[1]))
		lLine[2] = NB_LANDMARKS.index(int(lLine[2]))
		lLine[4] = MODELS.index(int(lLine[4]))
		lLine[5] = float(lLine[5])
		mRes[lLine[4], lLine[0], lLine[1], lLine[2], float(lLine[3])] += lLine[5]

mRes = np.mean(mRes, axis=4)

fig = plt.figure()
plt.clf()

SYM = ["none", "full"]

mRes[:, 1, :, :] = mRes[:, 2, :, :] 

for i in range(len(MODELS)):
	for j in range(len(SYM)):
		print len(SYM) * 100 + len(MODELS) * 10 + i + j
		ax = fig.add_subplot(len(SYM) * 100 + len(MODELS) * 10 + i  + j * len(MODELS) + 1)
		drawRes(mRes[i, j, :, :], ax)
		ax.set_title("model=%d | sym=%s"%(MODELS[i], SYM[j]))
		ax.set_xlabel('nb landmark')
		ax.set_xticklabels(NB_LANDMARKS)
		ax.set_ylabel('nb color')
		ax.set_yticklabels(NB_COLORS)
# cax = fig.add_axes([0.9, 0.1, 0.03, 0.8])
# fig.colorbar(im, cax=cax)

plt.show()
