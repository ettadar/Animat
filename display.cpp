#include "display.hpp"

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

Display::Display(std::vector<Cylinder*>* cylinderList):
  _screen(NULL),
  _cylinderList(cylinderList)
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetCaption("Animat", NULL);

  _screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_FillRect(_screen, NULL, SDL_MapRGB(_screen->format, 255, 255, 255));

  _cylinderColorList.reserve(NB_COLOR);
  _cylinderColorList[BLACK] = IMG_Load("Images/cylinder_black.png");
  _cylinderColorList[RED] = IMG_Load("Images/cylinder_red.png");
  _cylinderColorList[BLUE] = IMG_Load("Images/cylinder_blue.png");

  for (int i = 0; i < cylinderList->size(); i++)
  {
    SDL_Rect cylinderPos;
    cylinderPos.x = cylinderList->at(i)->x - cylinderList->at(i)->r;
    cylinderPos.y = cylinderList->at(i)->y - cylinderList->at(i)->r;
    SDL_Surface* scaledSurf =
      _scaleSurface(_cylinderColorList[cylinderList->at(i)->color],
		    cylinderList->at(i)->r * 2,
		    cylinderList->at(i)->r * 2);
    SDL_BlitSurface(scaledSurf, NULL, _screen, &cylinderPos);
    delete scaledSurf;
  }
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

SDL_Surface *Display::_scaleSurface(SDL_Surface *surface, int width, int height)
{
    if(!surface || !width || !height)
        return 0;
     
    SDL_Surface *_ret = SDL_CreateRGBSurface(surface->flags, width, height,
					     surface->format->BitsPerPixel,
					     surface->format->Rmask,
					     surface->format->Gmask,
					     surface->format->Bmask,
					     surface->format->Amask);
 
    double _stretch_factor_x = (static_cast<double>(width) /
				static_cast<double>(surface->w)),
        _stretch_factor_y = (static_cast<double>(height) /
			     static_cast<double>(surface->h));
 
    for(int y = 0; y < surface->h; y++)
        for(int x = 0; x < surface->w; x++)
            for(int o_y = 0; o_y < _stretch_factor_y; ++o_y)
                for(int o_x = 0; o_x < _stretch_factor_x; ++o_x)
                    putpixel(_ret,
			     static_cast<Sint32>(_stretch_factor_x * x) + o_x, 
			     static_cast<Sint32>(_stretch_factor_y * y) + o_y,
			     getpixel(surface, x, y));
 
    return _ret;
}
