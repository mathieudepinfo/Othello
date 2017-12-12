#include "Plateau.h"


Plateau::Plateau(Damier* dam, SDL_Rect* z, BanqueImage* bq)
	:ObjetGraphique(nullptr, z), damier(dam), autoriseMentor(true), autoriseAide(true),autoriseRetour(false), banque(bq),mentor(-10)
{
	clickable = true;
	type = PLATEAU;
	police = TTF_OpenFont("ariblk.ttf", z->w / 10);

}

///=====================================================

Plateau::Plateau( SDL_Rect* z,  BanqueImage* bq) 
	:ObjetGraphique(nullptr, z),autoriseMentor(true), autoriseAide(true), autoriseRetour(false), banque(bq),mentor(-10)
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
	int x = event->button.x ;
	int y = event->button.y ;

	getCase(i, j, x, y);
}

///=====================================================

void Plateau::getCase(int& i, int& j, int x, int y) {

	x -= zone->x;
	y -= zone->y;
	i = y / (zone->h / 8);
	j = x / (zone->w / 8);
}

///=====================================================

void Plateau::render(SDL_Renderer* renderer) {

	if (!visible) {
		return;
	}
	
	//on travaille sur un nouveau damier pour tout ce qui est assistance graphique
	Damier* damierc = new Damier(*damier);

	
	std::vector<int>* coupsRetournements=new std::vector<int>();
	std::vector<int>* coupsPossibles=new std::vector<int>();

	int sx, sy;
	SDL_GetMouseState(&sx, &sy);
	
	if (autoriseRetour) {//on met à jour coups retournements
		int i(-1), j(0);
		getCase(i, j, sx, sy);
		getRetournements(*coupsRetournements,*damier, joueur, i, j);

	}
	if (autoriseAide) { //on met à joue coups possibles
		possibilites(*coupsPossibles ,*damier, joueur);
	}

	for (int coup : *coupsRetournements) {
		if (coup == -10) break;
		damierc->setV(RETOURNEMENT, coup / 10, coup % 10);
	}
	for (int coup : *coupsPossibles) {
		if (coup == -10) break;
		damierc->setV(POSSIBLE, coup / 10, coup % 10);
	}
	
	if (mentor != -10) damierc->setV(MENTOR, mentor / 10, mentor % 10);

	//copie chaque case dans le renderer
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {

			//on recupère la zone associée à la case à copier
			SDL_Rect* zonePion = new SDL_Rect(); 
			zonePion->x = zone->x + (j *  zone->w / 8);
			zonePion->y = zone->y+i *  zone->h / 8;
			zonePion->w = zone->w/8;
			zonePion->h = zone->h/8;

			switch (damierc->getV(i, j)) {

			case BLANC:
				SDL_RenderCopy(renderer, banque->getImage("pionBlanc"), nullptr , zonePion);
				break;
			case NOIR:
				SDL_RenderCopy(renderer, banque->getImage("pionNoir"), nullptr , zonePion);
				break;

			case POSSIBLE:
				SDL_RenderCopy(renderer, banque->getImage("possible"), nullptr, zonePion);
				break;

			case VIDE:
				SDL_RenderCopy(renderer, banque->getImage("vide"), nullptr, zonePion);
				break;

			case MENTOR:
				if (autoriseMentor) {
					SDL_RenderCopy(renderer, banque->getImage("mentor"), nullptr, zonePion);
				}
				
				if (!autoriseRetour) {
					mentor=-10; //on reset le mentor
				}
				break;

			case RETOURNEMENT:
				if (joueur == BLANC) {
					SDL_RenderCopy(renderer, banque->getImage("retourNoir"), nullptr, zonePion);
				}
				else if (joueur == NOIR) {
					SDL_RenderCopy(renderer, banque->getImage("retourNoir"), nullptr, zonePion);
				}
			}

			delete zonePion;
		}
	}

	delete damierc;
	delete coupsPossibles;
	delete coupsRetournements;

	//si la partie est finie est que ce n'est pas l'écran d'accueil
	if (damier->getNp()>0 && testFin(*damier)) {
		afficheScore(renderer);
		clickable = false;
		return;
	}
}

///=====================================================

void Plateau::afficheScore(SDL_Renderer* renderer) {
	int gagnant(0);

	if (score(*damier, BLANC) > score(*damier, NOIR)) {
		gagnant = BLANC;
	}
	else if (score(*damier, BLANC) < score(*damier, NOIR)) {
		gagnant = NOIR;
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

	SDL_Rect position; //position d'affichage du texte dans le renderer
	position.x = zone->w / 6 + zone->x;
	position.w = 4*(zone->w/6) ;
	position.h = zone->h / 3;
	position.y = zone->h / 3 + zone->y;

	SDL_Color coulNoire = { 0,0,0 };//couleur du texte

	//affichage du texte
	SDL_Surface* textGraphique = TTF_RenderText_Blended(police, text, coulNoire);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textGraphique);
	SDL_RenderCopy(renderer, textTexture, nullptr, &position);

	//destruction des objets crées
	SDL_FreeSurface(textGraphique);
	SDL_DestroyTexture(textTexture);

}