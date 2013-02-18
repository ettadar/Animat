#ifndef SIMULATOR_HPP
# define SIMULATOR_HPP

# include <vector>

# include "type.hpp"
# include "robot.hpp"
# include "display.hpp"
# include "cylinder.hpp"
# include "model.hpp"


class Simulator
{
public:
  Simulator();
  ~Simulator();

  void run();
  void step();

private:
  Image* _getImage(float posX, float posY);

private:
  Display* _display;
  Robot* _robot;

  float _robotPosX;
  float _robotPosY;
  
  float _goalPosX;
  float _goalPosY;

  std::vector<Cylinder*>* _cylinderList;
  bool _continue;
  int _nbIter;
};

#endif // !SIMULATOR_HPP
