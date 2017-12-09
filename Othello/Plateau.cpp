#include "Plateau.h"


Plateau::Plateau(Damier* dam,SDL_Rect* z,BanqueImage* bq)
	:ObjetGraphique(nullptr,z),damier(dam),autoriseMentor(true),autoriseAide(true),banque(bq)
{
	clickable = true;
	type = PLATEAU;
	banque = bq;
	police = TTF_OpenFont("ariblk.ttf", z->w / 10);

}

///=====================================================

Plateau::Plateau( SDL_Rect* z,  BanqueImage* bq) 
	:ObjetGraphique(nullptr, z),autoriseMentor(true), autoriseAide(true), banque(bq)
{
	clickable = false;
	type = PLATEAU;
	int setup[8][8] = { 0 };
	damier = new Damier(setup);
	police = TTF_OpenFont("ariblk.ttf", z->w / 10);
}

///=====================================================

Plateau::~Plateau()
{
	SDL_DestroyTexture(image);
	delete damier;
}

///=====================================================

void Plateau::getCase(int& i, int& j, SDL_Event* event) {
	int x = event->button.x - zone->x;
	int y = event->button.y - zone->y;

	i = y / (zone->h/8);
	j = x / (zone->w/8);
}

///=====================================================

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
				SDL_RenderCopy(renderer, banque->getImage("pionBlanc"), nullptr , zonePion);
				break;
			case NOIR:
				SDL_RenderCopy(renderer, banque->getImage("pionNoir"), nullptr , zonePion);
				break;

			case POSSIBLE: //coup possible
				SDL_RenderCopy(renderer, banque->getImage("possible"), nullptr, zonePion);
				break;

			case VIDE:
				SDL_RenderCopy(renderer, banque->getImage("vide"), nullptr, zonePion);
				break;

			case MENTOR: //coup assisté
				if (autoriseMentor) {
					SDL_RenderCopy(renderer, banque->getImage("mentor"), nullptr, zonePion);
				}
				damier->setV(0, i, j);

				break;
			}

			delete zonePion;
		}
	}

	delete damierc;

	if (damier->getNp()>0 && testFin(*damier)) {
		afficheScore(renderer);
		clickable = false;
		return;
	}
}

///=====================================================

void Plateau::afficheScore(SDL_Renderer* renderer) {
	int gagnant(0);

	if (score(*damier, joueur) > score(*damier, 3-joueur)) {
		gagnant = joueur;
	}
	else if (score(*damier, joueur) < score(*damier, 3-joueur)) {
		gagnant = 3 - joueur;
	}

	char* text;
	if (gagnant== 1) {
		text = "Les blancs ont gagné !";
	}
	else if (gagnant == 2) {
		text = "Les noirs ont gagné !";
	}
	else {
		text = "Egalité";
	}

	SDL_Rect position;
	position.x = zone->w / 6 + zone->x;
	position.w = 4*(zone->w/6) ;
	position.h = zone->h / 3;
	position.y = zone->h / 3 + zone->y;

	SDL_Color coulNoire = { 0,0,0 };


	SDL_Surface* textGraphique = TTF_RenderText_Blended(police, text, coulNoire);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textGraphique);

	SDL_RenderCopy(renderer, textTexture, nullptr, &position);

	SDL_FreeSurface(textGraphique);
	SDL_DestroyTexture(textTexture);

}