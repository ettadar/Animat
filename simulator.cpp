#include "simulator.hpp"

#include <ctime>
#include <iostream>
#include <unistd.h>

Simulator::Simulator() :
  _display(NULL),
  _robotPosX(0),
  _robotPosY(0),
  _robot(Robot(std::vector<int>())),
  _cylinderList(NULL),
  _continue(true),
  _nbIter(0)
{
  // TODO : remove
  _getImage(0, 0);
  _cylinderList = new std::vector<Cylinder*>();
  
  _cylinderList->push_back(new Cylinder(100, 100, BLACK, 20));
  _cylinderList->push_back(new Cylinder(200, 200, RED, 20));
  _cylinderList->push_back(new Cylinder(200, 250, BLUE, 20));

  _display = new Display(_cylinderList);

  _display->setRobotPos(20, 20);
}

Simulator::~Simulator()
{
  _cylinderList->clear();
  delete _cylinderList;
  delete _display;
}

void Simulator::run()
{
  while (_continue)
  {
    //usleep(1000);
    step();
  }
}

void Simulator::step()
{
  _robot.step(std::vector<int>());
  _robotPosX += _robot.getMoveX();
  _robotPosY += _robot.getMoveY();

  _display->setRobotPos(_robotPosX, _robotPosY);
  _continue = _display->step();
}

Image* Simulator::_getImage(float posX, float posY)
{
  // Image* img = new Image();
  // for (int iPixel = 0; iPixel < IMAGE_SIZE; ++iPixel)
  // {
  //   float anglePixel = (iPixel - IMAGE_SIZE / 2) * (360 / VIEW_ANGLE);
  //   std::cout << anglePixel;
  //   float minDist;
  //   float iMinDist;
  // }
}