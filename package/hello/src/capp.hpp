#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL/SDL.h>

class CApp {

public:
    CApp();

    int OnExecute();

    static SDL_Surface* OnLoad(char* File);
    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);

    bool OnInit();

    void OnEvent(SDL_Event* Event);

    void OnLoop();

    void OnRender();

    void OnCleanup();

private:
    bool            Running;

    SDL_Surface*    Surf_Display;
    SDL_Surface*    Surf_Test;
};

#endif