#include "Plateau.h"


Plateau::Plateau(Damier* dam,SDL_Rect* z,BanqueImage* bq):ObjetGraphique(nullptr,z),damier(dam),autoriseMentor(true),autoriseAide(true)
{
	clickable = true;
	type = PLATEAU;
	banque = bq;

}


Plateau::Plateau( SDL_Rect* z,  BanqueImage* bq) :ObjetGraphique(nullptr, z),autoriseMentor(true), autoriseAide(true)
{
	clickable = false;
	type = PLATEAU;
	banque = bq;
	int setup[8][8] = { 0 };

	damier = new Damier(setup);
}

Plateau::~Plateau()
{
	SDL_DestroyTexture(image);
	delete damier;
}

void Plateau::getCase(int& i, int& j, SDL_Event* event) {
	int x = event->button.x - zone->x;
	int y = event->button.y - zone->y;

	i = y / (zone->h/8);
	j = x / (zone->w/8);
}

void Plateau::render(SDL_Renderer* renderer) {

	damier->affiche();
	//on travaille sur un nouveau damier pour tout ce qui est assistance graphique
	Damier* damierc = new Damier(*damier);

	//copie chaque case dans le renderer
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {

			SDL_Rect* zonePion = new SDL_Rect();
			zonePion->x = zone->x + (j *  zone->w / 8);
			zonePion->y = zone->y+i *  zone->h / 8;
			zonePion->w = zone->w/8;
			zonePion->h = zone->h/8;

			if (autoriseAide && damier->getV(i, j) != MENTOR && estValide(*damier, joueur, i, j)) {
				damierc->setV(POSSIBLE, i, j); //on affiche les possibilités
			}
			switch (damierc->getV(i, j)) {

			case BLANC:
				SDL_RenderCopy(renderer, banque->getImage("pionBlanc"), NULL, zonePion);
				break;
			case NOIR:
				SDL_RenderCopy(renderer, banque->getImage("pionNoir"), NULL, zonePion);
				break;

			case POSSIBLE: //coup possible
				SDL_RenderCopy(renderer, banque->getImage("possible"), NULL, zonePion);
				break;

			case VIDE:
				SDL_RenderCopy(renderer, banque->getImage("vide"), NULL, zonePion);
				break;

			case MENTOR: //coup assisté
				if (autoriseMentor) {
					SDL_RenderCopy(renderer, banque->getImage("mentor"), NULL, zonePion);
				}
				damier->setV(0, i, j);

				break;
			}

			delete zonePion;
		}
	}

	delete damierc;

	if (testFin(*damier)) {
		clickable = false;
		return;
	}
}