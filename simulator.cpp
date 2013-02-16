#include "simulator.hpp"

#include <ctime>
#include <iostream>

Simulator::Simulator() :
  _display(NULL),
  _cylinderList(NULL),
  _continue(true),
  _nbIter(0)
{
  _cylinderList = new std::vector<Cylinder*>();
  
  _cylinderList->push_back(new Cylinder(0, 0, BLACK, 40));
  _cylinderList->push_back(new Cylinder(200, 200, RED, 20));
  _cylinderList->push_back(new Cylinder(200, 200, BLUE, 10));

  _display = new Display(_cylinderList);
}

Simulator::~Simulator()
{
  _cylinderList->clear();
  delete _cylinderList;
  delete _display;
}

void Simulator::run()
{
  //const long double sysTime = time(0);
  //int lastTime = time(NULL);
  while (_continue)
  {
    //if (lastTime + )
    //sleep(0.1);
    step();
    //std::cout << time(0) << std::endl;
      //int lastTime = time(NULL);
  }
}

void Simulator::step()
{
  _continue = _display->step();
}
