#include "Interface.h"

///=================================================

int initSDL(){

    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stderr,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
    return 0;


}

///=================================================

void joueTour(MenuPrincipal* fenetre, Plateau* plateau, int difficulte, int typePartie, int i, int j) {

	
	fenetre->actualise();
	if (typePartie == IAVSIA) {
		plateau->joueur = 1;
		plateau->autoriseAide = false;
		while (!testFin(*(plateau->getDamier()))) {
			fenetre->actualise();

			Table* ttable = new Table();
			int coup = ID(5, difficulte, *(plateau->getDamier()), *ttable, plateau->joueur);
			delete ttable;

			i = coup / 10;
			j = coup % 10;

			joueCoup(*(plateau->getDamier()),plateau->joueur, i, j);
			plateau->joueur = 3 - plateau->joueur;
		}
		plateau->autoriseAide = true;
		return;
	}
	SDL_Event event;

	////////////////tour du joueur//////////////////
	if (estValide(*plateau->getDamier(), plateau->joueur, -1)) { i = -1; j = 0; }

	while (!estValide(*plateau->getDamier(), plateau->joueur, i, j)) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_MOUSEBUTTONUP: //joue coup joueur

			plateau->getCase(i, j, &event);

			break;

		case SDL_QUIT:
			exit(0);
			break;

		case SDL_KEYDOWN: //mentor
		{
			int imt, jmt;
			if (event.key.keysym.sym == SDLK_h) {
				int coup;
				alphaBeta(*(plateau->getDamier()), plateau->joueur, 5, MINI, MAXI, coup);
				if (coup < 0) {
					imt = -1;
					jmt = 0;
				}
				else {
					imt = coup / 10;
					jmt = coup % 10;
				}
				plateau->getDamier()->setV(5, imt, jmt);
				fenetre->actualise();
			}
		}break;

		}
	}

	joueCoup(*(plateau->getDamier()), plateau->joueur, i, j);
	fenetre->actualise();
	////////////////////////En fonction du type de partie tour de l'IA ou simplement changement de joueur/////////////////////
	if (typePartie == JVJ) {

		plateau->joueur = 3 - plateau->joueur;
	}
	else if (typePartie == JVSIA) {
		Table* ttable = new Table();
		plateau->autoriseAide = false;
		fenetre->actualise();
		
		int coup = ID(5, difficulte, *(plateau->getDamier()), *ttable, 3 - plateau->joueur);
		delete ttable;
		i = coup / 10;
		j = coup % 10;

		joueCoup(*(plateau->getDamier()), 3 - plateau->joueur, i, j);

		plateau->autoriseAide = true;
	}

	fenetre->actualise();
}