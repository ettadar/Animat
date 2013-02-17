#include "simulator.hpp"

#include <ctime>
#include <cmath>
#include <iostream>
#include <unistd.h>
#include <cfloat>

#include "model.hpp"

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
  _cylinderList = new std::vector<Cylinder*>();
  
  _cylinderList->push_back(new Cylinder(100, 100, RED, 20));
  _cylinderList->push_back(new Cylinder(140, 120, BLUE, 20));


  _display = new Display(_cylinderList);
  _display->setRobotView(_getImage(50, 100));

  _display->setRobotPos(20, 20);
  
  //ccmodel
  CCmodel* model = new CCmodel(_getImage(50, 100));
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
      float y2 = _cylinderList->at(iCylinder)->x - posY;
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
