#include "Plateau.h"

int Plateau::coupActuel = 0;

Plateau::Plateau(SDL_Renderer* r, Damier* dam, SDL_Rect* z, BanqueImage* bq)
	:ObjetGraphique(r,nullptr, z), damier(dam), autoriseMentor(true), autoriseAide(true),autoriseRetour(false), banque(bq),mentor(-10)
{
	clickable = true;
	type = PLATEAU;
	police = TTF_OpenFont("polices/ariblk.ttf", z->w / 10);
	historique = new std::vector<Plat_Save*>();

}

///=====================================================

Plateau::Plateau(SDL_Renderer* r, SDL_Rect* z,  BanqueImage* bq) 
	:ObjetGraphique(r,nullptr, z),autoriseMentor(true), autoriseAide(true), autoriseRetour(false), banque(bq),mentor(-10),difficulte(2), typePartie(JVJ)
{
	clickable = false;
	type = PLATEAU;
	int setup[8][8] = { 0 };
	damier = new Damier(setup);
	police = TTF_OpenFont("polices/ariblk.ttf", z->w / 10);
	historique = new std::vector<Plat_Save*>();
}

///=====================================================

Plateau::Plateau(const Plateau& p)
	:ObjetGraphique(p.renderer, p.image, p.zone), autoriseMentor(p.autoriseMentor), autoriseAide(p.autoriseAide), autoriseRetour(p.autoriseRetour)
	, joueur(p.joueur),banque(p.banque),police(p.police),mentor(p.mentor),difficulte(2),typePartie(JVJ),historique(p.historique)
{
	clickable = p.clickable;
	visible = p.visible;
	damier = new Damier(*p.damier);

}

///=====================================================

Plateau::~Plateau()
{
	SDL_DestroyTexture(image);
	delete damier;
	for (auto p : *historique) {
		if (p != nullptr) delete p;
	}
	delete historique;
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

void Plateau::render() {

	if (!visible) {
		return;
	}
	
	//on travaille sur un nouveau damier pour tout ce qui est assistance graphique
	Damier damierc = Damier(*damier);

	std::vector<int> coupsRetournements = std::vector<int>();
	std::vector<int> coupsPossibles = std::vector<int>();

	int sx, sy;
	SDL_GetMouseState(&sx, &sy);
	
	if (autoriseRetour) {//on met à jour coups retournements
		int i(-1), j(0);
		getCase(i, j, sx, sy);
		coupsRetournements=getRetournements(i, j);

	}
	if (autoriseAide) { //on met à joue coups possibles
		possibilites(coupsPossibles ,*damier, joueur);
	}

	for (auto coup : coupsRetournements) {
		if (coup == -10) break;
		damierc.setV(RETOURNEMENT, coup / 10, coup % 10);
	}
	for (auto coup : coupsPossibles) {
		if (coup == -10) break;
		damierc.setV(POSSIBLE, coup / 10, coup % 10);
	}
	
	if (autoriseMentor && mentor != -10) damierc.setV(MENTOR, mentor / 10, mentor % 10);

	//copie chaque case dans le renderer
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {

			//on recupère la zone associée à la case à copier
			SDL_Rect zonePion = SDL_Rect(); 
			zonePion.x = zone->x + (j *  zone->w / 8);
			zonePion.y = zone->y+i *  zone->h / 8;
			zonePion.w = zone->w/8;
			zonePion.h = zone->h/8;

			switch (damierc.getV(i, j)) {

			case BLANC:
				SDL_RenderCopy(renderer, banque->getImage("pionblanc"), nullptr , &zonePion);
				break;
			case NOIR:
				SDL_RenderCopy(renderer, banque->getImage("pionnoir"), nullptr , &zonePion);
				break;

			case POSSIBLE:
				SDL_RenderCopy(renderer, banque->getImage("possible"), nullptr, &zonePion);
				break;

			case VIDE:
				SDL_RenderCopy(renderer, banque->getImage("vide"), nullptr, &zonePion);
				break;

			case MENTOR:
				if (autoriseMentor) {
					SDL_RenderCopy(renderer, banque->getImage("mentor"), nullptr, &zonePion);
				}
				
				break;

			case RETOURNEMENT:
				if (joueur == BLANC) {
					SDL_RenderCopy(renderer, banque->getImage("retourNoir"), nullptr, &zonePion);
				}
				else if (joueur == NOIR) {
					SDL_RenderCopy(renderer, banque->getImage("retourNoir"), nullptr, &zonePion);
				}
			}

		}
	}

	//si la partie est finie est que ce n'est pas l'écran d'accueil
	if (damier->getNp()>0 && testFin(*damier)) {
		afficheScore();
		makeUnclickable();
		
	}

}

///=====================================================

void Plateau::afficheScore() {
	int gagnant(0);

	if (score(*damier, BLANC) > score(*damier, NOIR)) {
		gagnant = BLANC;
	}
	else if (score(*damier, BLANC) < score(*damier, NOIR)) {
		gagnant = NOIR;
	}

	char* text;
	if (gagnant== BLANC) {
		text = "Les blancs ont gagné !";
	}
	else if (gagnant == NOIR) {
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

///=====================================================

void Plateau::callback(const SDL_Event& e) {
	int x = e.button.x;
	int y = e.button.y;

	int i, j;
	getCase(i,j,x,y);

	bool resetMentor(false);

	switch (typePartie) {
		
		case JVJ:
			switch (e.type) {
			case SDL_MOUSEBUTTONUP:
				if (clickable) {

					resetMentor = joueTourJ(i, j);
					render();
					break;
				}

			case SDL_KEYDOWN:
				int touche = e.key.keysym.sym;
				if (touche == SDLK_h) {//mentor "h" pour help
					setMentor(5);
				}
				else if (touche == SDLK_u) {// "u" pour undo
					dejoueCoup(1);
				}
				break;
			}
			break;

		case JVSIA:
			switch (e.type) {
			case SDL_MOUSEBUTTONUP:
				if (clickable) {

					resetMentor = joueTourJ(i, j);
					render();
				}

				if (resetMentor) mentor = -10;
				else break;

				// on désactive les aides quand l'IA joue
				autoriseAide = false; autoriseRetour = false; autoriseMentor = false;

				render();
				SDL_RenderPresent(renderer);

				joueTourIA();
				autoriseAide = true; autoriseRetour = true; autoriseMentor = true;
				break;
			case SDL_KEYDOWN:
				int touche = e.key.keysym.sym;
				if (touche == SDLK_h) {//mentor "h" pour help
					setMentor(5);
				}
				else if (touche == SDLK_u) {// "u" pour undo
					dejoueCoup(1);
				}
				break;
			}
			break;

		case IAVSIA:
				
			bool toEnd(false);
			autoriseAide = false; autoriseRetour = false; autoriseMentor = false;
				
			if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_e) toEnd = true;

			if (toEnd) {//mode automatque jusqu'à la fin
				SDL_Event e2;
				while (!testFin(*damier) && toEnd) {
					SDL_PollEvent(&e2);
							
					if (e2.type == SDL_KEYDOWN && e2.key.keysym.sym == SDLK_a) return; //actualise l'affichage
					if (e2.type == SDL_KEYDOWN && e2.key.keysym.sym == SDLK_s) toEnd = false; //arrête le mode automatique

					joueTourIA();
					render();
					SDL_RenderPresent(renderer);
				}
			}
			else if (e.type==SDL_MOUSEBUTTONUP){
				joueTourIA();
				render();
				SDL_RenderPresent(renderer);
			}
			
			autoriseAide = true; autoriseRetour = true; autoriseMentor = true;
				
			break;
	}//fin switch typePartie 
	
	if (resetMentor) mentor = -10;
	render();
}

///=====================================================

void Plateau::demarrePartie(int type)
{
	for (auto p : *historique) {
		if (p != nullptr) delete p;
	}
	delete historique;
	historique = new std::vector<Plat_Save*>();
	
	coupActuel = 0;
	makeClickable();
	joueur = JOUEUR_INITIAL;
	setDamier(new Damier(DAMIER_INITIAL));
	typePartie=type;
}

///=====================================================

std::vector<int> Plateau::getRetournements(int k, int l) {

	Damier dam = Damier(*damier); //on travaille sur une copie

	std::vector<int> coups = std::vector<int>();

	//partie qui ressemeble à joueCoup cf Othello.cpp
	if (estValide(dam, joueur, k, l) && k<8 && l<8 && k >= 0 && l >= 0) {
		if (k >= 0) {

			dam.setV(joueur, k, l);

			int d[3] = { -1,0,1 };
			bool p_adv;
			int cpt;

			for (int i(0); i<3; ++i) {
				for (int j(0); j<3; ++j) {
					if (d[i] != 0 || d[j] != 0) {

						p_adv = false,
							cpt = 1;

						while (0 <= (k + cpt*d[i]) && (k + cpt*d[i])<8 && 0 <= (l + cpt*d[j]) && (l + cpt*d[j])<8
							&& dam.getV(k + cpt*d[i], l + cpt*d[j]) == 3 - joueur) {
							cpt++;
							p_adv = true;
						}

						if (0 <= (k + cpt*d[i]) && (k + cpt*d[i])<8 && 0 <= (l + cpt*d[j]) && (l + cpt*d[j])<8
							&& p_adv
							&& dam.getV(k + cpt*d[i], l + cpt*d[j]) == joueur) {
							for (int m(1); m<cpt; ++m) { //on ajoute tous les pions rencontres

								coups.push_back((k + m*d[i]) * 10 + l + m*d[j]);
							}
						}
					}
				}
			}
		}
	}
	return coups;
}

///=====================================================

bool Plateau::joueTourJ(int i, int j) {

	if (estValide(*damier, joueur, -1)) { i = -1; j = 0; }

	if (!estValide(*damier, joueur, i, j)) return false; //si le coup n'est pas valide on ne joue pas

	historique->push_back(new Plat_Save(*this));
	++coupActuel;
	joueCoup(*damier, joueur, i, j);
	changeJoueur();

	return true;
}

	

///==========================================================

void Plateau::joueTourIA() {

	int i(-1), j(0);

	render();

	Table* ttable = new Table();
	int coup = ID(5, difficulte, *damier, *ttable, joueur);
	delete ttable;

	i = coup / 10;
	j = coup % 10;

	joueCoup(*damier, joueur, i, j);
	changeJoueur();
	
}

///=============================================================

void Plateau::dejoueCoup(int n_Coups) {

	if (coupActuel - n_Coups < historique->size() && coupActuel - n_Coups >= 0) {
		(*historique)[coupActuel - n_Coups]->load(this);
		std::cout << historique->size() << " " << coupActuel << std::endl;
		for (int i = coupActuel - n_Coups; i < historique->size(); ++i) {
			if((*historique)[i]!=nullptr) delete (*historique)[i];
		}
		historique->resize(coupActuel - n_Coups);
		coupActuel -= n_Coups;
	}
	else {
		int a = 1;
		historique;
	}

}

///============Fonctions de Plat_Save===========

Plateau::Plat_Save::Plat_Save(const Plateau& p) {
	damier = new Damier(*(p.getDamier()));
	joueur = p.joueur;
}

void Plateau::Plat_Save::load(Plateau* p)
{
	p->setDamier(new Damier(*damier));
	p->joueur = joueur;
}

Plateau::Plat_Save::~Plat_Save()
{
	if (damier != nullptr) delete damier;
}
