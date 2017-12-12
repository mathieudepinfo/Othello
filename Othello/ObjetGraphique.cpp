#include "ObjetGraphique.h"
#include "SDL.h"


ObjetGraphique::ObjetGraphique(SDL_Texture* im,SDL_Rect* z)
{
	zone = z;
	image = im;
	visible = true;
}

///=============================

ObjetGraphique::ObjetGraphique(SDL_Texture * im, int anchorx, int anchory, int width, int height)
{

	zone = new SDL_Rect();
	zone->x = anchorx;
	zone->y = anchory;
	zone->w = width;
	zone->h = height;
	image = im;
	visible = true;
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


