#include <cstdlib>

#include "simulator.hpp"

int main(int argc, char** argv)
{
  if (argc >= 3)
  {
    if (argc == 6)
    {
      Simulator* sim = new Simulator(true, std::string(argv[1]), std::atoi(argv[2]));
      sim->setRobotPos(std::atoi(argv[4]), std::atoi(argv[5]));
      sim->run();
      delete sim;
      return 0;
    }
    else if (argc == 3)
    {
      Simulator* sim = new Simulator(false, std::string(argv[1]), std::atoi(argv[2]));
      sim->generatePerfImage();
      return 0;
    }
  }
  std::cerr << "Usage = " << argv[0] << " <scene_file> <model_number> [-r <robot_pos_x> <robot_pos_y>]" << std::endl;
  
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
