#include "drawable.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    int cnt = 0;
    bool Running = true;
    SDL_Event Event;
    char* filePath = "myimage.bmp";
    char text[20] = "11:23";

    struct Drawable* main_window = createWindowDrawable();
    struct Drawable* text_Test = createTextDrawable();
    struct Drawable* bmp_Test = createBMPDrawable();

    if (!main_window->OnInit(&main_window->drawable_surff, NULL)) {
        printf("On init failed %s!\n", SDL_GetError());
        return -1;
    }

    if (!bmp_Test->OnInit(&bmp_Test->drawable_surff, filePath)) {
        printf("On init failed %s!\n", SDL_GetError());
        return -1;
    }

    if (!text_Test->OnInit(&text_Test->drawable_surff, text)) {
        printf("On init failed %s!\n", SDL_GetError());
        return -1;
    }

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            switch(Event.type) {
            case SDL_QUIT:
                Running = false;
                break;
            case SDL_KEYDOWN:
                cnt++;
                SDL_itoa(cnt, text, 10);
                if (!text_Test->OnInit(&text_Test->drawable_surff, text)) {
                    printf("On init failed %s!\n", SDL_GetError());
                    return -1;
                }
                printf("SDL_KEYDOWN event\n");
                break;
            case SDL_KEYUP:
                printf("SDL_UP event\n");
                break;
            }
        }

        bmp_Test->OnRender(main_window->drawable_surff, bmp_Test->drawable_surff, 120, 0);
        text_Test->OnRender(main_window->drawable_surff, text_Test->drawable_surff, 150, 300);
        usleep(500000);
    }

    main_window->OnCleanup(main_window->drawable_surff);
    bmp_Test->OnCleanup(bmp_Test->drawable_surff);
    text_Test->OnCleanup(text_Test->drawable_surff);

    free(text_Test);
    free(bmp_Test);
    free(main_window);

    printf("%s %d ALL GOOD\n", __FUNCTION__, __LINE__);
    return 0;
}
