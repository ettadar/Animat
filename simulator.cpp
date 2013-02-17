#include "simulator.hpp"

#include <ctime>
#include <cmath>
#include <iostream>
#include <unistd.h>
#include <cfloat>

Simulator::Simulator() :
  _display(NULL),
  _robotPosX(100),
  _robotPosY(240),
  _cylinderList(NULL),
  _continue(true),
  _nbIter(0)
{
  _cylinderList = new std::vector<Cylinder*>();
  _cylinderList->push_back(new Cylinder(400, 200, RED, 20));
  _cylinderList->push_back(new Cylinder(300, 400, BLUE, 20));

  CCmodel* mod = new CCmodel(_getImage(40, 240));
  _robot = new Robot(mod);

  _display = new Display(_cylinderList);
  _display->setRobotPos(_robotPosX, _robotPosY);
}

Simulator::~Simulator()
{
  _cylinderList->clear();
  delete _cylinderList;

  delete _robot;
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
  //std::cout << "Simulator::step" << std::endl;
  Image* img = _getImage(_robotPosX, _robotPosY);

  _display->setRobotPos(_robotPosX, _robotPosY);
  _display->setRobotView(img);
  _continue = _display->update();

  _robot->step(img);
  _robotPosX += _robot->getMoveX();
  _robotPosY += _robot->getMoveY();
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
