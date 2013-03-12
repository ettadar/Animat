#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <vector>

#include "../cylinder.hpp"
#include "../const.hpp"

class Display
{
public:
  Display(std::vector<Cylinder*>* cylinderList, int width, int height);
  ~Display();
  bool update();
  void setRobotPos(float x, float y);
  void setRobotView(Image* img);
  void setTargetPos(float x, float y);
  void setTargetView(Image* img);

private:
  SDL_Surface* _screen;

  SDL_Surface* _robot;
  SDL_Rect _robotPos;
  
  SDL_Surface* _target;
  SDL_Rect _targetPos;

  std::vector<Cylinder*>* _cylinderList;
  std::vector<SDL_Surface*> _cylinderToDraw;

  std::vector<SDL_Surface*> _cylinderColorList;

  Image* _robotView;
  
  Image* _targetView;
};

#endif // !DISPLAY_HPP
