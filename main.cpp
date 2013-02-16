#include "simulator.hpp"

int main()
{
  Simulator* sim = new Simulator();
  sim->run();
  delete sim;
}
