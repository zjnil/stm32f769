#include "drawable.h"
#include "bmp_drawable.h"
#include "text_drawable.h"
#include "window_drawable.h"

static struct Drawable *createDrawable(bool (*OnInit)(SDL_Surface** drawable_surf, void* data),
                                void (*OnRender)(SDL_Surface* Surf_Display, SDL_Surface* drawable_surf, int x, int y),
                                void (*OnCleanup)(SDL_Surface* drawable_surf))
{
    struct Drawable* drawable = malloc(sizeof(struct Drawable));
    if (!drawable) {
        printf("Failed to allocate drawable!\n");
        return NULL;
    }

    drawable->drawable_surff = NULL;
    drawable->OnInit = OnInit;
    drawable->OnRender = OnRender;
    drawable->OnCleanup = OnCleanup;
    return drawable;
}

struct Drawable *createBMPDrawable()
{
    return createDrawable(BMPOnInit, BMPOnRender, BMPOnCleanup);
}

struct Drawable *createTextDrawable()
{
    return createDrawable(TextOnInit, TextOnRender, TextOnCleanup);
}

struct Drawable* createWindowDrawable()
{
    return createDrawable(WindowOnInit, NULL, WindowOnCleanup);
}
