// Othello.cpp : Defines the entry point for the console application.
//

#include "SDL.h"

#include <iostream>

#include "ObjetGraphique.h"
#include "MenuPrincipal.h"
#include "Plateau.h"
#include "Bouton.h"
#include <functional>
#include "Interface.h"
#ifdef WIN32
#include <shellapi.h>
#endif 
#ifndef WIN32
#include <unistd.h>
#include <stdlib.h>
#endif

void afficheAide() {
#ifdef WIN32
	
	ShellExecute(NULL,
		L"open",
		L"aide.pdf",
		NULL,
		NULL,
		SW_SHOWNORMAL);
#endif
#ifndef WIN32 //code pas teste ca marche surement pas
	char* cmd = firefox;
	char* path = new char[1000];
	char** args = new char*[2];
	getwd(path, 900 * sizeof(char));
	args[0] = cmd; args[1] = path;
	path = strcat(path, "aide.pdf");
	if (fork() == 0) execvp(cmd, args);
#endif
}

int main(int argc,char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Échec de l'initialisation de la SDL (%s)\n" << SDL_GetError() << std::endl;;
		exit(-1);
	}
	if (TTF_Init() == -1) {
		std::cerr << "error initializing SDL_ttf" << std::endl;
		exit(-1);
	}

	MenuPrincipal& fenetre = MenuPrincipal::getInstance();
	SDL_Renderer* r = fenetre.getRenderer();


	//////////////////////Création des objets de l'interface/////////////////////////
	
	ObjetGraphique::resetCompteur();

	SDL_Rect* zoneDamier = new SDL_Rect();
	zoneDamier->x = 100; zoneDamier->y = 0; zoneDamier->w = 800; zoneDamier->h = 800;
	Plateau* plateau = new Plateau(r,zoneDamier, fenetre.getBanque());

	//Boutons difficulté
	Bouton* boutonFacile =
		new Bouton(r,fenetre.getTexture("BoutonFacile"), fenetre.getTexture("BoutonFacilePressed"),
			std::function<void()>([&](void) { plateau->setDifficulte(2); }), 0, 105, 100, 100);
	Bouton* boutonMoyen =
		new Bouton(r,fenetre.getTexture("BoutonMoyen"), fenetre.getTexture("BoutonMoyenPressed"),
			std::function<void()>([&](void) { plateau->setDifficulte(5); }), 0, 210, 100, 100);
	Bouton* boutonDur =
		new Bouton(r,fenetre.getTexture("BoutonDur"), fenetre.getTexture("BoutonDurPressed"),
			std::function<void()>([&](void) { plateau->setDifficulte(25); }), 0, 315, 100, 100);

	//Boutons démarrage de partie
	Bouton* boutonStartJIA = 
		new Bouton(r, fenetre.getTexture("BoutonJVSIA"), fenetre.getTexture("BoutonJVSIAPressed"),
			std::function<void()>([&](void) { plateau->demarrePartie(JVSIA); }), 900, 105, 100, 100);
	Bouton* boutonStartIAIA = 
		new Bouton(r,fenetre.getTexture("BoutonIAVSIA"), fenetre.getTexture("BoutonIAVSIAPressed"),
			std::function<void()>([&](void) { plateau->demarrePartie(IAVSIA); }), 900, 210, 100, 100);
	Bouton* boutonStartJJ = 
		new Bouton(r,fenetre.getTexture("BoutonJVJ"), fenetre.getTexture("BoutonJVJPressed"),
			std::function<void()>([&](void) { plateau->demarrePartie(JVJ); }), 900, 315, 100, 100);

	
	//Boutons changement de joueur
	Bouton* boutonNoir =
		new Bouton(r,fenetre.getTexture("BoutonNoirs"), fenetre.getTexture("BoutonNoirsPressed")
			, std::function<void()>([&](void)
			{
			if (plateau->joueur == BLANC && plateau->getTypePartie() == JVSIA) plateau->joueTourIA();
				plateau->joueur=NOIR; 
			})
			, 0, 520, 100, 100);
	Bouton* boutonBlanc =
		new Bouton(r,fenetre.getTexture("BoutonBlanc"), fenetre.getTexture("BoutonBlancPressed"),
			std::function<void()>([&](void) 
			{	
				if (plateau->joueur == NOIR && plateau->getTypePartie() == JVSIA) plateau->joueTourIA(); 
				plateau->joueur = BLANC;
			})
			, 0, 625, 100, 100);
	
	Bouton* help = new Bouton(r, fenetre.getTexture("Help"), fenetre.getTexture("HelpPressed"),
		std::function<void()>([&](void)
	{
		afficheAide();
	})
		, 0, 0, 100, 100);

	fenetre.addItems(ObjetGraphique::getCompteur(),
		boutonStartJIA,boutonStartIAIA,boutonStartJJ,boutonMoyen,boutonDur,boutonFacile,plateau,boutonNoir,boutonBlanc,help);

	fenetre.render();
	
	///////////////////////Variables "globales" initiales///////////////////////
	SDL_Event e;
	bool continuer(true);
	ObjetGraphique* objetSelectionne(nullptr);

	///////////////////////Boucle de gestion des events/////////////////////////
	while (continuer) {

		if (plateau->getTypePartie() == JVJ) { //si partie JCJ on desactive le changement de joueur
			boutonBlanc->makeInvisible();
			boutonNoir->makeInvisible();
		}
		else {
			boutonBlanc->makeVisible();
			boutonNoir->makeVisible();
		}

		SDL_WaitEvent(&e);

		switch (e.type) {

		case SDL_QUIT://boutton exit
			continuer = false;
			break;

		default:
			fenetre.onEvent(e);
		}
		
	}

	SDL_Quit();
	TTF_Quit();
    return 0;
}

