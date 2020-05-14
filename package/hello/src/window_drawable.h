#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL/SDL.h>
#include <stdbool.h>

bool WindowOnInit(SDL_Surface** Surf_Display, void* data);
void WindowOnCleanup(SDL_Surface* Surf_Display);

#endif
