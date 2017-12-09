#pragma once

///======================Classe Plateau=========================

#include "ObjetGraphique.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Damier.h"
#include "BanqueImage.h"
#include "Othello.h"
#include "Consts.h"
#include <string> 

/**
 * Classe représentant un plateau de jeu associé à un damier, un plateau est clickable s'il représente une partie en cours
 */
class Plateau : public ObjetGraphique
{
	
private:
	Damier* damier;
	BanqueImage* banque;
	TTF_Font* police;
	
public:

	bool autoriseAide;	
	bool autoriseMentor;
	int joueur;

	Plateau(SDL_Rect* z, BanqueImage* bq);

	Plateau(Damier* damier, SDL_Rect* z, BanqueImage* bq);

	~Plateau();

	void render(SDL_Renderer* renderer);
	
	/**
	 * retourne via i et j les coordonnées case clickée
	 * @param i recoit la ligne de la case
	 * @param j recoit la colonne de la case
	 */
	void getCase(int& i, int& j,SDL_Event* event);

	void setDamier(Damier* dam) {
		delete damier;
		damier=dam;
	}
	
	Damier* getDamier() {
		return damier;
	}

	void afficheScore(SDL_Renderer* renderer);
};

