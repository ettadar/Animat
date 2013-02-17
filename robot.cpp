#include "robot.hpp"

#include <cstdlib>

Robot::Robot(Model* model)
{
	_model = model;
	_moveX = 0;
	_moveY = 0;
}

Robot::~Robot()
{
	delete _model;
}

void Robot::step(Image* view)
{
	_moveX = -0.1;//((float)(rand() % 200 - 100)) / 100.;
	_moveY = 0;//((float)(rand() % 200 - 100)) / 100.;
}

float Robot::getMoveX()
{
	return _moveX;
}

float Robot::getMoveY()
{
	return _moveY;
}
