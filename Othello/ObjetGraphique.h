#pragma once

///====================================Classe ObjetGraphique========

#include "SDL.h"
#include "Consts.h"

/**
 * Classe mère de tout objet présent dans un MenuPrincipal
 * -contient une image
 * -contient une zone d'affichage/hitbox
 * -un attribut clickable 
 * -un attribut visible
 * -un attribut type
 * -un renderer auquel sur lequel est affiché l'objet
 * Elle contient aussi un compteur statique auquel on accède via getCompteur et resetCompteur
 */

class ObjetGraphique
{
	static int compteur;

protected:
	SDL_Renderer* renderer;
	SDL_Rect* zone;
	SDL_Texture* image;

	bool clickable;
	bool visible;

public:

	int type;

	//fonctions statiques
	static void resetCompteur() {
		compteur = 0;
	}
	static int getCompteur(){
		return compteur;
	}
	static void incrementeCompteur() {
		++compteur;
	}
	//constructeurs
	ObjetGraphique(SDL_Renderer* r,SDL_Texture* im,SDL_Rect* zone);

	ObjetGraphique(SDL_Renderer* r,SDL_Texture* im, int anchorx,int anchory,int width,int height);

	//destructeur
	virtual ~ObjetGraphique() {};

	//fonction d'affichage, à implémenter dans les classes filles
	virtual void render() = 0;

	virtual SDL_Rect* getZone() {
		return zone;
	}
	/*Fonction définnissant la hitbox, pas besoin d'être redéfinie pour objets rectangulaires*/
	virtual bool isInZone(int x, int y);

	//fonction appelée lorsque qu'un event doit être traité par l'objet
	virtual void callback(const SDL_Event &event)=0;

	virtual void makeVisible();
	virtual void makeInvisible();

	virtual void makeClickable();
	virtual void makeUnclickable();

	virtual bool isClickable() { return clickable; }

};


