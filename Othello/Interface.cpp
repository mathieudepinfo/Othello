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

void joueTour(MenuPrincipal* fenetre, Plateau* plateau, int joueur,int difficulte, int typePartie, int i, int j) {

	fenetre->actualise(); 

	if (typePartie == IAVSIA) {
		joueIAVSIA(fenetre, plateau, difficulte);
	}

	if (joueur == plateau->joueur) { //joueur représente le joueur humain, plateau->joueur représente le joueur qui doit jouer le prochain coup 
		if (estValide(*plateau->getDamier(), plateau->joueur, -1)) { i = -1; j = 0; }

		if (!estValide(*plateau->getDamier(), plateau->joueur, i, j)) return; //si le coup n'est pas valide on ne joue pas
			
		joueCoup(*(plateau->getDamier()), plateau->joueur, i, j);
		plateau->joueur = 3 - plateau->joueur;
		fenetre->actualise();
	}
	
	if (3 - joueur == plateau->joueur &&  typePartie == JVSIA) { //si c'est au tour de l'IA de jouer
		Table* ttable = new Table();
		plateau->autoriseAide = false; //on ne veut pas afficher d'aide ou de mentor
		plateau->autoriseMentor = false;
		fenetre->actualise();

		//calcul du coup en fonction de la difficulte
		int coup = ID(5, difficulte, *(plateau->getDamier()), *ttable, plateau->joueur);

		delete ttable;

		i = coup / 10;
		j = coup % 10;

		//on joue le coup 
		joueCoup(*(plateau->getDamier()), plateau->joueur, i, j);
		plateau->joueur = 3 - plateau->joueur;

		//on réactive les aides car après l'IA c'est au tour du joueur
		plateau->autoriseAide = true;
		plateau->autoriseMentor = true;
	}
	else if (3 - joueur == plateau->joueur &&  typePartie == JVJ) { 

		if (!estValide(*plateau->getDamier(), plateau->joueur, i, j)) return;

		joueCoup(*(plateau->getDamier()), plateau->joueur, i, j);
		plateau->joueur = 3 - plateau->joueur;
		fenetre->actualise();
	}
	

	fenetre->actualise();
	
}

///==========================================================

void joueIAVSIA(MenuPrincipal* fenetre, Plateau* plateau, int difficulte) {

	int i(-1), j(0);

	plateau->joueur = 1;
	plateau->autoriseAide = false; //on désactive les aides
	plateau->autoriseMentor = false;

	SDL_Event event;

	while (!testFin(*(plateau->getDamier()))) {
		SDL_PollEvent(&event); //evite le gel de l'interface et permet de quitter le programme
		if (event.type == SDL_QUIT) exit(0);
		fenetre->actualise();

		Table* ttable = new Table();
		int coup = ID(5, difficulte, *(plateau->getDamier()), *ttable, plateau->joueur);
		delete ttable;

		i = coup / 10;
		j = coup % 10;

		joueCoup(*(plateau->getDamier()), plateau->joueur, i, j);
		plateau->joueur = 3 - plateau->joueur;
	}

	//on réactive les aides
	plateau->autoriseAide = true;
	plateau->autoriseMentor = true;
	fenetre->actualise();
}

///==========================================================

void getRetournements(std::vector<int>& coups,const Damier& dam, int joueur, int k, int l) {
	Damier damier = Damier(dam); //on travaille sur une copie

	//partie qui ressemeble à joueCoup cf Othello.cpp
	if (estValide(damier, joueur, k, l) && k<8 && l<8 && k>=0 && l>=0) {
		if (k >= 0) {

			damier.setV(joueur, k, l);

			int d[3] = { -1,0,1 };
			bool p_adv;
			int cpt;

			for (int i(0); i<3; ++i) {
				for (int j(0); j<3; ++j) {
					if (d[i] != 0 || d[j] != 0) {

						p_adv = false,
							cpt = 1;

						while (0 <= (k + cpt*d[i]) && (k + cpt*d[i])<8 && 0 <= (l + cpt*d[j]) && (l + cpt*d[j])<8
							&& damier.getV(k + cpt*d[i], l + cpt*d[j]) == 3 - joueur) {
							cpt++;
							p_adv = true;
						}

						if (0 <= (k + cpt*d[i]) && (k + cpt*d[i])<8 && 0 <= (l + cpt*d[j]) && (l + cpt*d[j])<8
							&& p_adv
							&& damier.getV(k + cpt*d[i], l + cpt*d[j]) == joueur) {
							for (int m(1); m<cpt; ++m) { //on ajoute tous les pions rencontres

								coups.push_back( (k + m*d[i])*10+ l + m*d[j]);
							}
						}
					}
				}
			}
		}

	}
}
