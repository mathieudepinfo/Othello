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
#include "IterativeDeepening.h"
#include <vector>

/**
 * Classe repr�sentant un plateau de jeu associ� � un damier, un plateau est clickable s'il repr�sente une partie en cours
 * -damier est le damier encapsul� dans Plateau, c'est sur ce damier que se d�roule la partie
 * -banque est la banque d'image qui contient les images des pions (noir, blanc, mentor ...)
 * -police est la police de caract�res lors de l'affichage du vainqueur en fin de partie
 * -mentor est la case ou jouerait l'IA
 * -joueur est le joueur qui doit jouer le prochain coup
 * -autoriseMentor, autoriseRetour et autoriseAide sont des indicateurs utiles lors de l'affichage
 * -typePartie est le type de partie en cours sur le plateau JVJ , JVSIA, IAVSIA
 * -difficulte repr�sente le niveau de l'IA
 */


class Plateau : public ObjetGraphique
{
	
private:

	class Plat_Save {
		Damier* damier;
		int joueur;

	public:
		Plat_Save(const Plateau& p);
		void load(Plateau* p);
		~Plat_Save();
	};

	std::vector<Plat_Save*>* historique;
	Damier* damier;
	BanqueImage* banque;
	TTF_Font* police;
	int mentor;
	int typePartie;
	int difficulte;

	static int coupActuel;

public:

	bool autoriseAide;	
	bool autoriseMentor;
	bool autoriseRetour;
	
	int joueur;

	//Constructeurs
	Plateau(SDL_Renderer* r,SDL_Rect* z, BanqueImage* bq);

	Plateau(SDL_Renderer* r,Damier* damier, SDL_Rect* z, BanqueImage* bq);

	Plateau(const Plateau&);

	//Destructeur
	~Plateau();

	//fonction d'affichage
	void render() override;
	
	/**
	 * retourne via i et j les coordonn�es case click�e
	 * @param i recoit la ligne de la case
	 * @param j recoit la colonne de la case
	 * @param event l'event contenant les coordonn�es n�cessaires
	 */
	void getCase(int& i, int& j,SDL_Event* event);
	void getCase(int& i, int& j, int sx,int sy);

	void setDamier(Damier* dam) {
		delete damier;
		damier=dam;
	}
	
	Damier* getDamier()const {
		return damier;
	}
	
	/**
	 * Fonction qui affiche un texte en fin de partie sur renderer
	 */
	void afficheScore();

	/**
	 * Met � jour le mentor, mentor qui joueura avec une profondeur "prof"
	 */
	void setMentor(char prof) {
		alphaBeta(*damier, joueur, prof, MINI, MAXI, mentor);
	}
	
	void setDifficulte(char diff) {
		difficulte = diff;
	}
	void setTypePartie(int type) {
		typePartie = type;
	}

	int getTypePartie() {
		return typePartie;
	}
	
	void changeJoueur() {
		joueur = 3 - joueur;
	}

	void callback(const SDL_Event& e) override;

	void demarrePartie(int type);

	/*Fonction qui retourne un vecteur contenant tous les pions qui se retourneraient si on joue en (k,l)*/
	std::vector<int> getRetournements(int k, int l);

	/*L'IA joue le coup suivant */
	void joueTourIA();
	/*Le joueur joue en (i,j) , retourne un bool�en qui indique si le coup a �t� jou� ou non*/
	bool joueTourJ(int i, int j);

	void dejoueCoup(int n_coups);

};

