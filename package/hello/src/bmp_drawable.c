#include "bmp_drawable.h"

bool BMPOnInit(SDL_Surface** drawable_surf, void* data)
{
    SDL_Surface* Surf_Temp = NULL;

    if ((Surf_Temp = SDL_LoadBMP((char*)data)) == NULL) {
        printf("Failed to load image %s!\n", SDL_GetError());
        return false;
    }

    if (*drawable_surf) {
        SDL_FreeSurface(*drawable_surf);
        *drawable_surf = NULL;
    }

    *drawable_surf = SDL_DisplayFormat(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);
    if (*drawable_surf == NULL) {
        printf("Failed to load image %s!\n", SDL_GetError());
        return false;
    }

    return true;
}

void BMPOnRender(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y)
{
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        printf("Rendering failed!\n");
        return;
    }

    SDL_Rect DestR;
    DestR.x = x;
    DestR.y = y;
    DestR.w = Surf_Src->w;
    DestR.h = Surf_Src->h;

//    static SDL_Rect old_DestR;
//    SDL_FillRect(Surf_Dest, &old_DestR, 0x000000); // clear old image
//    old_DestR = DestR;

    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

    SDL_Flip(Surf_Dest); //is needed??
}

void BMPOnCleanup(SDL_Surface* drawable_surf)
{
    SDL_FreeSurface(drawable_surf);
}
