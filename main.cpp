#include "simulator.hpp"

int main()
{
  Simulator* sim = new Simulator();
  sim->run();
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
