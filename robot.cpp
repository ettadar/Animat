#include "robot.hpp"

#include <cstdlib>

#include "landscape.hpp"

Robot::Robot(const std::vector<int>& goalView)
{
	_moveX = 0;
	_moveY = 0;
}

Robot::~Robot()
{
}

void Robot::step(const std::vector<int>& view)
{
	_moveX = ((float)(rand() % 200 - 100)) / 100.;
	_moveY = ((float)(rand() % 200 - 100)) / 100.;
}

float Robot::getMoveX()
{
	return _moveX;
}

float Robot::getMoveY()
{
	return _moveY;
}