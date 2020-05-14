#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SDL.h>
#include <stdbool.h>

struct Drawable {
    SDL_Surface* drawable_surff;
    bool (*OnInit)(SDL_Surface** drawable_surf, void* data);
    void (*OnRender)(SDL_Surface* Surf_Display, SDL_Surface* drawable_surf, int x, int y);
    void (*OnCleanup)(SDL_Surface* drawable_surf);
};

struct Drawable* createBMPDrawable();
struct Drawable* createTextDrawable();
struct Drawable* createWindowDrawable();

#endif // DRAWABLE_H
