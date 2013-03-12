CC=g++
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=-lSDL -lGL -lGLU -lSDL_image
SRC= \
robot.cpp \
simulator.cpp \
\
display/display.cpp \
display/Image.cpp \
display/perfimage.cpp \
display/sdlhelper.cpp \
\
model/ccmodel.cpp \
model/dynamicmodelcolor.cpp \
model/dynamicmodel.cpp \
model/dynamicmodelnocolor.cpp \
model/dynamicradial.cpp \
model/dynamicradialoneobject.cpp

OBJ= $(SRC:.cpp=.o)

all: animat_exp animat_one_run

animat_exp: $(OBJ) main_exp.o
	$(CC) -o $@ $^ $(LDFLAGS); mv animat_exp ../

animat_one_run: $(OBJ) main_one_run.o
	$(CC) -o $@ $^ $(LDFLAGS); mv animat_one_run ../

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean mrproper

clean:
	rm -rf *.o *~ */*.o */*~
