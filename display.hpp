#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <vector>

#include "cylinder.hpp"
#include "robot.hpp"

class Display
{
public:
  Display(std::vector<Cylinder*>* cylinderList);
  ~Display();
  bool step();
  void setRobotPos(float x, float y);
  void setRobotView(Image* img);

private:
  SDL_Surface* _screen;

  SDL_Surface* _robot;
  SDL_Rect _robotPos;

  std::vector<Cylinder*>* _cylinderList;
  std::vector<SDL_Surface*> _cylinderToDraw;

  std::vector<SDL_Surface*> _cylinderColorList;

  Image* _robotView;
};

#endif // !DISPLAY_HPP
