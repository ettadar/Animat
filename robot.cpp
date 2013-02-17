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
	_model->computeMove(view);
	_moveX = _model->getMoveX();
	_moveY = _model->getMoveY();//((float)(rand() % 200 - 100)) / 100.;
	std::cout<<"taille de x "<<_moveX<<std::endl;
	std::cout<<"taille de y "<<_moveY<<std::endl;
}

float Robot::getMoveX()
{
	return _moveX;
}

float Robot::getMoveY()
{
	return _moveY;
}
