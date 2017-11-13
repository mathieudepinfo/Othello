#include "Interface.h"


int initSDL(){

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
    return 0;


}

int menu(SDL_Window* fenetre,SDL_Renderer* renderer)
{

    SDL_Surface * image = SDL_LoadBMP("Plateau.bmp");
    SDL_Texture * plateau = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect* zoneDamier=new SDL_Rect();
    zoneDamier->x=100;
    zoneDamier->y=0;
    zoneDamier->w=800;
    zoneDamier->h=800;

    bool quit(false);
    SDL_Event event;

    while (!quit)
    {
        SDL_WaitEvent(&event);

        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
        }

        //SDL_Rect dstrect = { 5, 5, 320, 240 };
        //SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderCopy(renderer, plateau, NULL, zoneDamier);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(plateau);
    SDL_FreeSurface(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);

    SDL_Quit();
}
