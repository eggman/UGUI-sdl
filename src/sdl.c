#include "SDL.h"

#include "ugui.h"

static SDL_Surface *screen;
static UG_GUI gui;

UG_WINDOW window_1;
#define MAX_OBJECTS        10
UG_OBJECT obj_buff_wnd_1[MAX_OBJECTS];
UG_BUTTON button1_1;
UG_TEXTBOX text1_1;

void window_1_callback( UG_MESSAGE* msg )
{
    if (msg->type == MSG_TYPE_OBJECT)
    {
        if(msg->id == OBJ_TYPE_BUTTON)
        {
            if (msg->event == OBJ_EVENT_PRESSED || msg->event == OBJ_EVENT_CLICKED)
            {
                if( msg->sub_id == BTN_ID_0)
                    UG_TextboxSetText(&window_1, TXB_ID_0, "HELLO WORLD!");
            }
        }
    }
}

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

    UG_WindowCreate( &window_1, obj_buff_wnd_1, MAX_OBJECTS, window_1_callback );
    UG_WindowSetTitleTextFont( &window_1, &FONT_8X8 );
    UG_WindowSetTitleText( &window_1, "UGUI with SDL" );

    UG_ButtonCreate( &window_1, &button1_1, BTN_ID_0, 10, 10, 110, 60 );
    UG_ButtonSetFont( &window_1, BTN_ID_0, &FONT_8X8 );
    UG_ButtonSetText( &window_1, BTN_ID_0, "Start" );

    UG_TextboxCreate(&window_1, &text1_1, TXB_ID_0, 120, 10, 220, 120);
    UG_TextboxSetFont(&window_1, TXB_ID_0, &FONT_8X8);
    UG_TextboxSetText(&window_1, TXB_ID_0, "hello world!");
    UG_TextboxSetAlignment(&window_1, TXB_ID_0, ALIGN_TOP_RIGHT);
    UG_WindowShow( &window_1 );

    do{
        if (SDL_PollEvent(&e) != 0){
            switch(e.type){
            case SDL_QUIT:
                done = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                UG_TouchUpdate(e.button.x,e.button.y,TOUCH_STATE_PRESSED);
                break;
            case SDL_MOUSEBUTTONUP:
                UG_TouchUpdate(-1,-1,TOUCH_STATE_RELEASED);
                break;
            }
        }

        UG_Update();
        SDL_UpdateRect(screen,0,0,0,0);
    }while(!done);

    SDL_Quit();
    return 0;
}
