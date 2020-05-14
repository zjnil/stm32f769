#ifndef TEXT_DRAWABLE_H
#define TEXT_DRAWABLE_H

#include <stdbool.h>
#include <SDL.h>

bool TextOnInit(SDL_Surface** drawable_surf, void* data);
void TextOnRender(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y);
void TextOnCleanup(SDL_Surface* drawable_surf);

#endif // TEXT_DRAWABLE_H
