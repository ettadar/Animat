CC=g++
CFLAGS=-W -Wall -ansi -pedantic -O3
LDFLAGS=-lSDL -lGL -lGLU -lSDL_image
SRC= \
ccmodel.cpp \
cylinder.hpp \
display.cpp \
dynamicmodelcolor.cpp \
dynamicmodel.cpp \
dynamicmodelnocolor.cpp \
dynamicradial.cpp \
Image.cpp \
perfimage.cpp \
robot.cpp \
sdlhelper.cpp \
simulator.cpp

OBJ= $(SRC:.cpp=.o)

all: animat_exp animat_one_run

animat_exp: $(OBJ) main_exp.o
	$(CC) -o $@ $^ $(LDFLAGS)

animat_one_run: $(OBJ) main_one_run.o
	$(CC) -o $@ $^ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean mrproper

clean:
	rm -rf *.o *~

mrproper: clean
	rm -rf animat_exp animat_one_run
