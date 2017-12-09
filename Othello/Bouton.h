#pragma once

///=============================Fichier contenant la classe Bouton et ses d�riv�es=============

#include "Consts.h"
#include "SDL.h"
#include "Plateau.h"

/**
 * Classe qui repr�sente un bouton sans action, �tend la classe ObjetGraphique, pas de classe virtuelle action car param�tres diff�rents
 * En soi cette classe ne fournit qu'un destructeur commun et pourrait ne pas exister mais elle donne du sens au code
 */
class Bouton:public ObjetGraphique
{

public:
	//Constructeurs
	Bouton(SDL_Texture* im, SDL_Rect* zone);

	Bouton(SDL_Texture* im,int anchorx, int anchory, int width, int height);

	//Destructeur
	~Bouton();

	//Fonction d'affichage
	void render(SDL_Renderer* renderer);

};

/**
 * Bouton qui repr�sente un niveau de difficult� via son attribut pmax
 */
class BoutonNiveau : public Bouton
{

	int pmax; //profondeur max de jeu de l'IA

public:
	//Constructeurs
	BoutonNiveau(SDL_Texture* im, SDL_Rect* zone, int p) :Bouton(im, zone), pmax(p) { type = BOUTON_NIVEAU; };

	BoutonNiveau(SDL_Texture* im, int anchorx,int anchory,int width,int height, int p) :Bouton(im, anchorx,anchory,width,height), pmax(p) { type = BOUTON_NIVEAU; };

	//action li�e au bouton
	void action(int& difficulte) {
		difficulte = pmax;
	}
};

/**
* Bouton qui permet de d�marrer une partie
*/
class BoutonStart : public Bouton
{
private:
	int typePartie; //les types possibles sont JVJ IAVSIA et JVSIA
public:

	//Constructeurs
	BoutonStart(SDL_Texture* im, SDL_Rect* zone,int partie) :Bouton(im, zone),typePartie(type){ type = BOUTON_START; };

	BoutonStart(SDL_Texture* im,int partie, int anchorx, int anchory, int width, int height) :Bouton(im, anchorx, anchory, width, height),typePartie(partie){ type = BOUTON_START; };

	/**
	 * D�marre une partie sur l'objet plateau associ�
	 * @param plateau le plateau de jeu
	 * @param j le joueur si partie contre IA
	 * @param type le type de partie
	 * @param fenetre la fenetre qui contient plateau
	 */
	void action(Plateau* plateau,int& type);

	int getType()const {
		return typePartie;
	}
};

