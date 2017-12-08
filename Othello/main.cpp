#include <iostream>
#include "Partie.h"
#include <unistd.h>
#include "testia.h"
#include "Interface.h"
#include <SDL2/SDL.h>
using namespace std;

int main(int argc,char* argv[])
{
   /*int setup[8][8]=
    {
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,2,0,0,0},
        {0,0,0,1,2,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
    };

    int cont[8][8]=
    {
        {3,5,5,5,5,5,5,3},
        {5,8,8,8,8,8,8,5},
        {5,8,8,8,8,8,8,5},
        {5,8,8,8,8,8,8,5},
        {5,8,8,8,8,8,8,5},
        {5,8,8,8,8,8,8,5},
        {5,8,8,8,8,8,8,5},
        {3,5,5,5,5,5,5,3},
    };
    Damier* dam=new Damier(setup,cont);
    int n_coups;
    int joueur=1;
    int coups[64][2]={0};

    possibilites(coups,*dam,n_coups,joueur);
    for(int i(0);i<n_coups;i++){
        printf("%d %d %d\n",n_coups,coups[i][0],coups[i][1]);
    }*/
    //test();
    char prof=static_cast<char>(atoi(argv[1]));
    IAVSIA(prof);
    //playerVSIA(1);
/*
    SDL_Window* pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,1000,800,SDL_WINDOW_SHOWN);
    SDL_Renderer* pRenderer=SDL_CreateRenderer(pWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    menu(pWindow,pRenderer);
;*/
    return 0;
}
