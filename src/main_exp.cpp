#include <cstdlib>
#include <iostream>

#include "simulator.hpp"

int main(int argc, char** argv)
{
  if (argc == 5)
  {
    Simulator* sim = new Simulator(false, std::string(argv[1]), std::atoi(argv[2]),
    	std::string(argv[3]), std::string(argv[4]));
    sim->generatePerfImage();
    delete sim;
    return 0;
  }
  if (argc == 4)
  {
    Simulator* sim = new Simulator(false, std::string(argv[1]), std::atoi(argv[2]),
    	std::string(argv[3]));
    sim->generatePerfImage();
    delete sim;
    return 0;
  }
  std::cerr << "Usage = " << argv[0] << " <scene_file> <model_number> <image_file.tga> [<results_file>]" << std::endl;
}
