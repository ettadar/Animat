#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <vector>

#include "cylinder.hpp"

class Display
{
public:
  Display(std::vector<Cylinder*>* cylinderList);
  ~Display();
  bool step();
  void setRobotPos(float x, float y);

private:
  SDL_Surface * _scaleSurface(SDL_Surface *Surface, int width, int height);

private:
  SDL_Surface* _screen;

  SDL_Surface* _robot;
  SDL_Rect _robotPos;

  std::vector<Cylinder*>* _cylinderList;
  std::vector<SDL_Surface*> _cylinderToDraw;

  std::vector<SDL_Surface*> _cylinderColorList;
};

#endif // !DISPLAY_HPP
