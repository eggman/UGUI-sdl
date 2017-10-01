#include "SDL.h"

static SDL_Surface *screen;

int main (int argc, char **argv)
{
    SDL_Event e;
    int done = 0;

    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(480,320,24,SDL_HWSURFACE);

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
