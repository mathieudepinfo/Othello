#include "ObjetGraphique.h"
#include "SDL.h"

int ObjetGraphique::compteur = 0;

ObjetGraphique::ObjetGraphique(SDL_Renderer* r,SDL_Texture* im,SDL_Rect* z)
	:zone(z),image(im),visible(true), renderer(r)
{
	incrementeCompteur();
}

///=============================

ObjetGraphique::ObjetGraphique(SDL_Renderer* r,SDL_Texture * im, int anchorx, int anchory, int width, int height)
	:image(im),visible(true),renderer(r)
{
	zone = new SDL_Rect();
	zone->x = anchorx;
	zone->y = anchory;
	zone->w = width;
	zone->h = height;
	incrementeCompteur();
}

///=============================

bool ObjetGraphique::isInZone(int x, int y)
{
	return (
			(zone->x < x)
			&& (x < zone->x + zone->w)
			&& (zone->y < y)
			&& (y < zone->y + zone->h)
			);
}

///===============================

void ObjetGraphique::makeVisible() {
	visible = true;
}
void ObjetGraphique::makeInvisible(){
	visible = false;
}

void ObjetGraphique::makeClickable() {
	clickable = true;
}
void ObjetGraphique::makeUnclickable() {
	clickable = false;
}