#pragma once

///======================Classe Plateau=========================

#include "SDL.h"
#include "SDL_ttf.h"

#include "ObjetGraphique.h"
#include "BanqueImage.h"

#include "Damier.h"
#include "Othello.h"
#include "Consts.h"
#include "IA_ab.h"

#include <vector>

#include "Interface.h"

/**
 * Classe représentant un plateau de jeu associé à un damier, un plateau est clickable s'il représente une partie en cours
 * -damier est le damier encapsulé dans Plateau, c'est sur ce damier que se déroule la partie
 * -banque est la banque d'image qui contient les images des pions (noir, blanc, mentor ...)
 * -police est la police de caractères lors de l'affichage du vainqueur en fin de partie
 * -mentor est la case ou jouerait l'IA
 * -joueur est le joueur qui doit jouer le prochain coup
 * -autoriseMentor, autoriseRetour et autoriseAide sont des indicateurs utiles lors de l'affichage
 */
class Plateau : public ObjetGraphique
{
	
private:
	Damier* damier;
	BanqueImage* banque;
	TTF_Font* police;
	int mentor;

public:

	bool autoriseAide;	
	bool autoriseMentor;
	bool autoriseRetour;
	
	int joueur;

	//Constructeurs
	Plateau(SDL_Rect* z, BanqueImage* bq);

	Plateau(Damier* damier, SDL_Rect* z, BanqueImage* bq);

	//Destructeur
	~Plateau();

	//fonction d'affichage
	void render(SDL_Renderer* renderer);
	
	/**
	 * retourne via i et j les coordonnées case clickée
	 * @param i recoit la ligne de la case
	 * @param j recoit la colonne de la case
	 * @param event l'event contenant les coordonnées nécessaires
	 */
	void getCase(int& i, int& j,SDL_Event* event);
	void getCase(int& i, int& j, int sx,int sy);

	void setDamier(Damier* dam) {
		delete damier;
		damier=dam;
	}
	
	Damier* getDamier() {
		return damier;
	}
	
	/**
	 * Fonction qui affiche un texte en fin de partie sur renderer
	 */
	void afficheScore(SDL_Renderer* renderer);

	/**
	 * Met à jour le mentor, mentor qui joueura avec une profondeur "prof"
	 */
	void setMentor(char prof) {
		alphaBeta(*damier, joueur, prof, MINI, MAXI, mentor);
	}

	void changeJoueur() {
		joueur = 3 - joueur;
	}
};

