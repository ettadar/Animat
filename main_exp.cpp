#include <cstdlib>

#include "simulator.hpp"

int main(int argc, char** argv)
{
  if (argc == 3)
  {
    Simulator* sim = new Simulator(false, std::string(argv[1]), std::atoi(argv[2]));
    sim->generatePerfImage();
    delete sim;
    return 0;
  }
  std::cerr << "Usage = " << argv[0] << " <scene_file> <model_number>" << std::endl;
}
