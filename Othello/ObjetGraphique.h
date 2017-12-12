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
 */
class ObjetGraphique
{
	
protected:

	SDL_Rect* zone;
	SDL_Texture* image;

public:

	int type;
	bool clickable;
	bool visible;

	//constructeurs
	ObjetGraphique(SDL_Texture* im,SDL_Rect* zone);

	ObjetGraphique(SDL_Texture* im, int anchorx,int anchory,int width,int height);

	//destructeur
	virtual ~ObjetGraphique() {};

	//fonction d'affichage, à implémenter dans les filles
	virtual void render(SDL_Renderer* renderer) = 0;

	virtual SDL_Rect* getZone() {
		return zone;
	}

	virtual bool isInZone(int x, int y);

};

