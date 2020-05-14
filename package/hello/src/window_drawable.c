#include "drawable.h"

bool WindowOnInit(SDL_Surface** Surf_Display, void* data)
{
    (void)(data); // unused

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }

    if((*Surf_Display = SDL_SetVideoMode(480, 800, 16, SDL_HWSURFACE /* | SDL_FULLSCREEN*/)) == NULL) {
        printf("Set video mode failed!\n");
        return false;
    }

    return true;
}

void WindowOnCleanup(SDL_Surface* Surf_Display)
{
    printf("On cleanup\n");
    SDL_FreeSurface(Surf_Display);
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}
