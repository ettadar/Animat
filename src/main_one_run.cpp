#include <cstdlib>
#include <iostream>

#include "simulator.hpp"

int main(int argc, char** argv)
{
  if (argc == 5)
  {
    Simulator* sim = new Simulator(true, std::string(argv[1]), std::atoi(argv[2]));
    sim->setRobotPos(std::atoi(argv[3]), std::atoi(argv[4]));
    sim->run();
    delete sim;
    return 0;
  }
  std::cerr << "Usage = " << argv[0] << " <scene_file> <model_number> <robot_pos_x> <robot_pos_y>" << std::endl;
}
