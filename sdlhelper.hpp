#include <SDL/SDL.h>

Uint32 getpixel(SDL_Surface *surface, int x, int y);

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

SDL_Surface* scaleSurface(SDL_Surface *surface, int width, int height);

SDL_Surface* createSurface(int width, int height, const SDL_Surface* display);
