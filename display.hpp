#ifndef DISPLAY_HPP
# define DISPLAY_HPP

#include <GL/gl.h>             	//header file for openGL
#include <GL/glu.h>                //header file for the openGL utility library
#include <GL/glut.h>           	//header file for GLUT
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Display
{
public:
  Display();
  ~Display();
  bool step();

private:
  SDL_Surface* _screen;
  SDL_Surface* _cylinderSurf;
  SDL_Rect _cylinderPos;
};

#endif // !DISPLAY_HPP
