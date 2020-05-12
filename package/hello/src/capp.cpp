#include "capp.hpp"

CApp::CApp() {
    Surf_Test = NULL;
    Surf_Display = NULL;

    Running = true;
}

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(480, 800, 16, SDL_HWSURFACE /* | SDL_FULLSCREEN*/)) == NULL) {
        printf("Set video mode failed!\n");
        return false;
    }

    if((Surf_Test = CApp::OnLoad("myimage.bmp")) == NULL) {
        printf("Failed to load image!\n");
        return false;
    }

    return true;
}

SDL_Surface* CApp::OnLoad(char* File) {
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

    if((Surf_Temp = SDL_LoadBMP(File)) == NULL) {
        return NULL;
    }

    Surf_Return = SDL_DisplayFormat(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);

    return Surf_Return;
}

bool CApp::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

    return true;
}

void CApp::OnEvent(SDL_Event* Event) {
	printf("%s %d type: %d\n", __FUNCTION__, __LINE__, Event->type);
    if(Event->type == SDL_QUIT) {
        Running = false;
    }
}

void CApp::OnCleanup() {
	printf("%s %d\n", __FUNCTION__, __LINE__);
    SDL_FreeSurface(Surf_Test);
    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}

void CApp::OnRender() {
    CApp::OnDraw(Surf_Display, Surf_Test, 0, 0);

    SDL_Flip(Surf_Display); //is needed??
}

void CApp::OnLoop() {
}

int CApp::OnExecute() {
	printf("%s %d\n", __FUNCTION__, __LINE__);
    if (OnInit() == false) {
        printf("%s %d\n", __FUNCTION__, __LINE__);
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    printf("%s %d ALL GOOD\n", __FUNCTION__, __LINE__);
    return 0;
}