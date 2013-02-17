#include "display.hpp"

#include "robot.hpp"
#include "sdlhelper.hpp"

Display::Display(std::vector<Cylinder*>* cylinderList):
_screen(NULL),
_cylinderList(cylinderList),
_cylinderToDraw(std::vector<SDL_Surface*>())
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Animat", NULL);

	_screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_FillRect(_screen, NULL, SDL_MapRGB(_screen->format, 255, 255, 255));

	_cylinderColorList.reserve(NB_COLOR);
	_cylinderColorList[BLACK] = IMG_Load("Images/cylinder_black.png");
	_cylinderColorList[RED] = IMG_Load("Images/cylinder_red.png");
	_cylinderColorList[BLUE] = IMG_Load("Images/cylinder_blue.png");

	for (int i = 0; i < cylinderList->size(); i++)
	{
		SDL_Surface* scaledSurf =
		scaleSurface(_cylinderColorList[cylinderList->at(i)->color],
			cylinderList->at(i)->r * 2,
			cylinderList->at(i)->r * 2);
		_cylinderToDraw.push_back(scaledSurf);
	}

	_robot = scaleSurface(IMG_Load("Images/Bee.jpg"),
		ROBOT_SIZE, ROBOT_SIZE);
}

Display::~Display()
{
	_cylinderToDraw.clear();
	SDL_Quit();
}

bool Display::step()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch(event.type)
	{
		case SDL_QUIT:
		return false;
	}

	// Clear screen
	SDL_FillRect(_screen, NULL, SDL_MapRGB(_screen->format, 255, 255, 255));

	// Draw cylinders
	for (int i = 0; i < _cylinderToDraw.size(); i++)
	{
		SDL_Rect cylinderPos;
		cylinderPos.x = _cylinderList->at(i)->x - _cylinderList->at(i)->r;
		cylinderPos.y = _cylinderList->at(i)->y - _cylinderList->at(i)->r;
		SDL_BlitSurface(_cylinderToDraw[i], NULL, _screen, &cylinderPos);
	}

	// Draw robot
	SDL_BlitSurface(_robot, NULL, _screen, &_robotPos);

	SDL_Flip(_screen);

	return true;
}

void Display::setRobotPos(float x, float y)
{
	_robotPos.x = x - ROBOT_SIZE / 2;
	_robotPos.y = y - ROBOT_SIZE / 2;
}
