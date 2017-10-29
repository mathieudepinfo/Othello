#include "Interface.h"


int initSDL(){

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
    return 0;

}

int menu(SDL_Window& fenetre)
{

}
