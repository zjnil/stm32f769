#include "text_drawable.h"
#include <SDL/SDL_ttf.h>

static struct _TTF_Font* mFont = NULL;

bool TextOnInit(SDL_Surface** drawable_surf, void* data)
{
    char* fontPath = "/root/arial.ttf";

    // initialize TTF system for text rendering.
    if (!TTF_WasInit() && TTF_Init() == -1) {
        printf("Unable to initialize TTF: %s\n", TTF_GetError());
        return false;
    }

    // initialize a font for the application.
    if (!mFont) {
        mFont = TTF_OpenFont(fontPath, 60);
        if (!mFont) {
            printf("Unable to load font: %s\n", TTF_GetError());
            return false;
        }
    }

    if (*drawable_surf) {
        SDL_FreeSurface(*drawable_surf);
        *drawable_surf = NULL;
    }

    SDL_Color color = {255, 255, 255, 0};
    if (!(*drawable_surf = TTF_RenderText_Solid(mFont, (char*)data,  color))) {
        printf("Text rendering failed: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

void TextOnRender(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int x, int y)
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

void TextOnCleanup(SDL_Surface* drawable_surf)
{
    SDL_FreeSurface(drawable_surf);
    TTF_CloseFont(mFont);
    TTF_Quit();
}
