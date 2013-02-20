#include "simulator.hpp"

int main(int argc, char** argv)
{
  Simulator* sim = new Simulator(false/*scene, typeModel*/);
  if (argc > 1)
  {
    // --one-run
    sim->setRobotPos(240, 100);
    sim->run();
  }
  else
  {
    sim->generatePerfImage();
  }
  delete sim;
  
  /*Image* img = new Image();
  
  img->push_back(1);
  img->push_back(1);
  img->push_back(1);
  img->push_back(1);
  
  img->push_back(0);
  img->push_back(0);
  img->push_back(0);
  
  img->push_back(1);
  img->push_back(1);
  img->push_back(1);
  
  img->push_back(0);
  img->push_back(0);
  img->push_back(0);
  
  img->push_back(1);
  
  img->push_back(0);
  
  CCmodel* model = new CCmodel(img);
  delete model; */
}
