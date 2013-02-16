#include "simulator.hpp"

#include <ctime>
#include <iostream>

Simulator::Simulator() :
  _display(Display()),
  _continue(true),
  _nbIter(0)
{
  // TODO
}

Simulator::~Simulator()
{
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
  _continue = _display.step();
}
