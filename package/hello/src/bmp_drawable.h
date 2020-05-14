#ifndef BMP_DRAWABLE_H
#define BMP_DRAWABLE_H

#include <stdbool.h>
#include <SDL.h>

bool BMPOnInit(SDL_Surface** drawable_surf, void* data);
void BMPOnRender(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y);
void BMPOnCleanup(SDL_Surface* drawable_surf);

#endif // BMP_DRAWABLE_H
