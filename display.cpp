#include "display.hpp"

Display::Display():
  _screen(NULL),
  _cylinderSurf(NULL)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Animat", NULL);

  _screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
  SDL_FillRect(_screen, NULL, SDL_MapRGB(_screen->format, 255, 255, 255));

  _cylinderSurf = IMG_Load("Images/cylinder_black.png");
  _cylinderPos.x = 300;
  _cylinderPos.y = 300;

  SDL_BlitSurface(_cylinderSurf, NULL, _screen, &_cylinderPos);
}

Display::~Display()
{
  SDL_Quit();
}

bool Display::step()
{
  SDL_Event event;
  SDL_PollEvent(&event);
  switch(event.type)
  {
  case SDL_QUIT:
    return false;
    // case SDL_KEYDOWN:
    //   switch(event.key.keysym.sym){
    //     case SDLK_LEFT:
    // 	  body->applyCentralForce(btVector3(-10,0,0));
    //       break;
    //     case SDLK_RIGHT:
    // 	  body->applyCentralForce(btVector3(10,0,0));
    //       break;
    //     case SDLK_UP:
    // 	  body->applyCentralForce(btVector3(0,0,-10));
    //       break;
    //     case SDLK_DOWN:
    // 	  body->applyCentralForce(btVector3(0,0,10));
    //       break;
    //     default:
    //       break;
    //   }
  }

  SDL_Flip(_screen);

  return true;
}
