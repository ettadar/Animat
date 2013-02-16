#ifndef SIMULATOR_HPP
# define SIMULATOR_HPP

# include <list>

# include "robot.hpp"
# include "display.hpp"
# include "cylinder.hpp"

class Simulator
{
public:
  Simulator();
  ~Simulator();

  void run();
  void step();

private:
  Display _display;
  Robot _robot;
  std::list<Cylinder*> _cylinderList;

  bool _continue;
  int _nbIter;
};

#endif // !SIMULATOR_HPP
