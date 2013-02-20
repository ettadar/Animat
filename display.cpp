#include "display.hpp"

#include "sdlhelper.hpp"

Display::Display(std::vector<Cylinder*>* cylinderList, int width, int height):
_screen(NULL),
_cylinderList(cylinderList),
_cylinderToDraw(std::vector<SDL_Surface*>()),
_robotView(0)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Animat", NULL);

	_screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
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
		
	_target = scaleSurface(IMG_Load("Images/target.png"),
		ROBOT_SIZE, ROBOT_SIZE);
}

Display::~Display()
{
	_cylinderToDraw.clear();
	SDL_Quit();
}

bool Display::update()
{
	SDL_Event event;
	SDL_WaitEvent(&event);
	if (event.type == SDL_QUIT)
	{
		std::cout << "SDL_QUIT" << std::endl;
		return true;
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

	// Draw target
	SDL_BlitSurface(_target, NULL, _screen, &_targetPos);

	// Draw robot
	SDL_BlitSurface(_robot, NULL, _screen, &_robotPos);	

	// Draw goal view
	if (_targetView != 0)
	{
		SDL_Rect pos;
		pos.x = 0;
		pos.y = 10;
		SDL_Surface* surf = createSurface(VIEW_ANGLE + 1, 10, _screen);
		for (int i = 0; i < VIEW_ANGLE + 1; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (_targetView->at(i) == BLACK)
					putpixel(surf, i, j, 0x000000);
				else if (_targetView->at(i) == RED)
					putpixel(surf, i, j, 0xFF0000);
				else if (_targetView->at(i) == BLUE)
					putpixel(surf, i, j, 0x0000FF);
			}
		}
		SDL_BlitSurface(surf, NULL, _screen, &pos);
	}

	// Draw robot view
	if (_robotView != 0)
	{
		SDL_Rect pos;
		pos.x = 0;
		pos.y = 0;
		SDL_Surface* surf = createSurface(VIEW_ANGLE + 1, 10, _screen);
		for (int i = 0; i < VIEW_ANGLE + 1; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				if (_robotView->at(i) == BLACK)
					putpixel(surf, i, j, 0x000000);
				else if (_robotView->at(i) == RED)
					putpixel(surf, i, j, 0xFF0000);
				else if (_robotView->at(i) == BLUE)
					putpixel(surf, i, j, 0x0000FF);
			}
		}
		SDL_BlitSurface(surf, NULL, _screen, &pos);
	}

	SDL_Flip(_screen);

	return false;
}

void Display::setRobotPos(float x, float y)
{
	_robotPos.x = x - ROBOT_SIZE / 2;
	_robotPos.y = y - ROBOT_SIZE / 2;
}

void Display::setRobotView(Image* img)
{
	_robotView = img;
}

void Display::setTargetPos(float x, float y)
{
	_targetPos.x = x - ROBOT_SIZE / 2;
	_targetPos.y = y - ROBOT_SIZE / 2;
}

void Display::setTargetView(Image* img)
{
	_targetView = img;
}

