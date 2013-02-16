#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include <GL/gl.h>             	//header file for openGL
#include <GL/glu.h>                //header file for the openGL utility library
#include <GL/glut.h>           	//header file for GLUT
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

private:
  SDL_Surface * _scaleSurface(SDL_Surface *Surface, int width, int height);

private:
  SDL_Surface* _screen;
  std::vector<Cylinder*>* _cylinderList;

  std::vector<SDL_Surface*> _cylinderColorList;
};

#endif // !DISPLAY_HPP
