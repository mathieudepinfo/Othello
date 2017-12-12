#include "Bouton.h"

Bouton::Bouton(SDL_Texture* im,SDL_Rect* zone) :ObjetGraphique(im, zone)
{
	this->type = BOUTON;
	this->clickable = true;
}

///==========================================

Bouton::Bouton(SDL_Texture* im, int anchorx, int anchory, int width, int height) :ObjetGraphique(im, anchorx, anchory, width, height)
{
	this->clickable = true;
	this->type = BOUTON;
}

///==========================================

Bouton::~Bouton()
{
	delete zone;
}

///==========================================

void Bouton::render(SDL_Renderer* renderer) {
	if (visible) {
		SDL_RenderCopy(renderer, image, NULL, zone);
	}
}

///==========================================

void BoutonStart::action(Plateau* plateau,int& type) {

	plateau->clickable = true;

	int setup[8][8] =
	{
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,1,2,0,0,0 },
		{ 0,0,0,2,1,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0 },
	};
	plateau->setDamier(new Damier(setup));
	plateau->joueur = 1;
	type = typePartie;
}