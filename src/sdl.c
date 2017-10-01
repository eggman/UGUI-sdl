#include "SDL.h"

#include "ugui.h"

static SDL_Surface *screen;
static UG_GUI gui;

void sdl_pset(uint16_t x, uint16_t y, uint32_t c)
{
    SDL_Rect dest;
    Uint32 color; 
    color = SDL_MapRGB(screen->format, c>>16&0xff, c>>8&0xff, c&0xff); // R G B
    dest.w = 1;
    dest.h = 1;
    dest.x = x;
    dest.y = y;
    SDL_FillRect(screen,&dest,color);
}

int main (int argc, char **argv)
{
    SDL_Event e;
    int done = 0;

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(480,320,24,SDL_HWSURFACE);

    UG_Init(&gui,(void(*)(UG_S16,UG_S16,UG_COLOR))sdl_pset,480,320);
    UG_FillScreen( C_BLUE );

    do{
        if (SDL_PollEvent(&e) != 0){
            switch(e.type){
            case SDL_QUIT:
                done = 1;
                break;
            }
        }

        SDL_UpdateRect(screen,0,0,0,0);
    }while(!done);

    SDL_Quit();
    return 0;
}
