// Othello.cpp : Defines the entry point for the console application.
//

#include "SDL.h"
#include "SDL_ttf.h"

#include "Partie.h"
#include "Interface.h"
#include "MenuPrincipal.h"

const int IA = 1;

int main(int argc,char* argv[])
{
	initSDL();
	if (TTF_Init() == -1) {
		std::cout << "error initializing SDL_ttf" << std::endl; exit(-1);
	}

	MenuPrincipal* fenetre = MenuPrincipal::getInstance();
	
	//////////////////////Création des objets de l'interface/////////////////////////
	
	Bouton* boutonFacile =	new BoutonNiveau(fenetre->getTexture("boutonFacile"), 0, 105, 100, 100,2);
	Bouton* boutonMoyen =	new BoutonNiveau(fenetre->getTexture("boutonMoyen"), 0, 210, 100, 100,5);
	Bouton* boutonDur =		new BoutonNiveau(fenetre->getTexture("boutonDur"), 0, 315, 100, 100,15);

	Bouton* boutonStartJIA = new BoutonStart(fenetre->getTexture("boutonJVSIA"), JVSIA, 900, 105, 100, 100);
	Bouton* boutonStartIAIA = new BoutonStart(fenetre->getTexture("boutonIAVSIA"), IAVSIA, 900, 210, 100, 100);
	Bouton* boutonStartJJ = new BoutonStart(fenetre->getTexture("boutonJVJ"), JVJ, 900, 315, 100, 100);

	SDL_Rect* zoneDamier = new SDL_Rect();
	zoneDamier->x = 100;zoneDamier->y = 0;zoneDamier->w = 800;zoneDamier->h = 800;
	Plateau* plateau = new Plateau(zoneDamier,fenetre->getBanque());

	fenetre->addItem(boutonStartJIA); fenetre->addItem(boutonStartIAIA); fenetre->addItem(boutonStartJJ); 
	fenetre->addItem(boutonMoyen); fenetre->addItem(boutonDur); fenetre->addItem(boutonFacile); fenetre->addItem(plateau);
	fenetre->actualise();
	
	//variables "globales" initiales
	SDL_Event event;
	int difficulte	=2;
	int joueur		=1;
	int typePartie	=JVJ;
	ObjetGraphique* objetSelectionne;


	while (1) {

		SDL_WaitEvent(&event);

		switch (event.type) {

		case SDL_QUIT://boutton exit
			delete fenetre;
			exit(0);
			break;

		case SDL_MOUSEBUTTONUP:
		
			objetSelectionne = fenetre->getObjectOnMouseClick(event);
			if (objetSelectionne == nullptr) break;

			//pas de switch car problème avec les déclarations de variables et aucun besoin de gain en performance ici
			if (objetSelectionne->type == BOUTON_NIVEAU) {

				static_cast<BoutonNiveau*>(objetSelectionne)->action(difficulte);
				std::cout << difficulte << std::endl;
				fenetre->actualise();
			}

			else if (objetSelectionne->type == PLATEAU) //plateau cliquable, une partie est donc en cours avec au moins un humain
			{
				int i = -1; int j = 0;

				static_cast<Plateau*>(objetSelectionne)->getCase(i, j, &event);
				
				joueTour(fenetre, static_cast<Plateau*>(objetSelectionne), difficulte,typePartie, i, j);
				fenetre->actualise();
			}
			else if(objetSelectionne->type == BOUTON_START) { //bouton qui démarre une partie

				static_cast<BoutonStart*>(objetSelectionne)->action(plateau,typePartie);
				fenetre->focusedObject = plateau;
				fenetre->actualise();
			}
				
		
			break;
		
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_h) {
				if (fenetre->focusedObject->type == PLATEAU) {
					mentor(static_cast<Plateau*>(fenetre->focusedObject));
					fenetre->actualise();
				}
			}

			break;
		}//fin du switch

		
	}

	delete fenetre;
	SDL_Quit();
	TTF_Quit();
    return 0;
}

