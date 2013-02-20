#include "simulator.hpp"

#include <ctime>
#include <cmath>
#include <iostream>
#include <unistd.h>
#include <cfloat>

Simulator::Simulator(bool display) :
  _display(NULL),
  _robotPosX(0),
  _robotPosY(0),
  _goalPosX(100),
  _goalPosY(240),
  _cylinderList(NULL),
  _continue(true),
  _windowClosed(false),
  _nbIter(0)
{
  _cylinderList = new std::vector<Cylinder*>();
  _cylinderList->push_back(new Cylinder(400, 100, RED, 20));
  _cylinderList->push_back(new Cylinder(350, 350, BLUE, 20));

  Image* timg = _getImage(_goalPosX, _goalPosY);
  CCmodel* mod = new CCmodel(timg);
  _robot = new Robot(mod);

  if (display)
  {
    _display = new Display(_cylinderList);
    _display->setTargetPos(_goalPosX, _goalPosY);
    _display->setTargetView(timg);
    _display->setRobotPos(_robotPosX, _robotPosY);
  }
}

Simulator::~Simulator()
{
  _cylinderList->clear();
  delete _cylinderList;

  delete _robot;
  delete _display;
}

void Simulator::setRobotPos(float robotPosX, float robotPosY)
{
  _robotPosX = robotPosX;
  _robotPosY = robotPosY;
}

void Simulator::run()
{
  while (_continue && !_windowClosed)
  {
    //usleep(1000000);
    step();
  }

  if (_display)
    while (!_windowClosed)
      _windowClosed = _display->update();    
}

void Simulator::generatePerfImage()
{

}

void Simulator::step()
{
  Image* img = _getImage(_robotPosX, _robotPosY);

  if (_display)
  {
    _display->setRobotPos(_robotPosX, _robotPosY);
    _display->setRobotView(img);
    _windowClosed = _display->update();
  }

  _robot->step(img);
  _robotPosX += _robot->getMoveX();
  _robotPosY += _robot->getMoveY();

  if (_robot->getMoveX() == 0 && _robot->getMoveY() == 0)
    _continue = false;
}

// WARNING : Do not handle differant size cylinder
Image* Simulator::_getImage(float posX, float posY)
{
  Image* img = new Image();
  for (int iPixel = 0; iPixel < VIEW_ANGLE + 1; ++iPixel)
  {
    float angle = (iPixel - VIEW_ANGLE / 2) / 360. * 2 * PI;
    float minDist = FLT_MAX;
    int color = BLACK;

    for (int iCylinder = 0; iCylinder < _cylinderList->size(); ++iCylinder)
    {
      float x1 = cos(angle);
      float y1 = sin(angle);
      x1 /= sqrt(pow(x1, 2) + pow(y1, 2));
      y1 /= sqrt(pow(x1, 2) + pow(y1, 2));

      float x2 = _cylinderList->at(iCylinder)->x - posX;
      float y2 = _cylinderList->at(iCylinder)->y - posY;
      // std::cout << x2 << ", " << y2 << std::endl;

      float prod = x1 * x2 + y1 * y2;
      // std::cout << "prod : " << prod << std::endl;
      if (prod <= 0)
        continue;

      float squareDist = pow(x1 * prod - x2, 2) + pow(y1 * prod - y2, 2);
      // std::cout << "dist : " << squareDist << std::endl;
      if (squareDist > pow(_cylinderList->at(iCylinder)->r, 2))
        continue;

      if (prod < minDist)
      {
        minDist = prod;
        color = _cylinderList->at(iCylinder)->color;
      }
    }
    img->push_back(color);
  }
  return img;
}
