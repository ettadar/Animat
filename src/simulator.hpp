#ifndef SIMULATOR_HPP
# define SIMULATOR_HPP

# include <vector>
# include <string>
# include <set>

# include "robot.hpp"
# include "cylinder.hpp"
# include "display/display.hpp"

class Simulator
{
public:
  Simulator(bool display, std::string sceneFile, int modelNumber, std::string imageFile="", std::string resultsFile="");
  ~Simulator();

  void setRobotPos(float robotPosX, float robotPosY);
  void run();
  void generatePerfImage();
  void step();

private:
  Image* _getImage(float posX, float posY);

private:
  Display* _display;
  Robot* _robot;

  int _sceneWidth;
  int _sceneHeight;

  float _robotPosX;
  float _robotPosY;
  
  float _goalPosX;
  float _goalPosY;

  std::vector<Cylinder*>* _cylinderList;

  bool _success;
  bool _continue;
  bool _windowClosed;

  int _nbIter;
  std::set<std::pair<float, float> > _knownPos;
  std::set<std::pair<int, int> > _currOkPos;
  std::vector<std::vector<int> > _goodOrBadPos;

  std::string _imageFile;
  std::string _resultsFile;
};

#endif // !SIMULATOR_HPP
