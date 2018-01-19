#pragma once

///=============================Fichier contenant la classe Bouton=============

#include "Consts.h"
#include "SDL.h"
#include "ObjetGraphique.h"
#include <functional>
/**
 * Classe qui représente un bouton, étend la classe ObjetGraphique
 */
class Bouton:public ObjetGraphique
{
private:
	
	std::function<void()> actionFunction;

public:
	SDL_Texture* imageDown; //possibilité de rajouter une image à afficher lors d'un click

	//Constructeurs
	
	Bouton(SDL_Renderer* r, SDL_Texture* im, SDL_Texture* imd, std::function<void()> f, SDL_Rect* zone)
		:ObjetGraphique(r, im, zone), actionFunction(f), imageDown(imd)
	{
		type = BOUTON; clickable = true; 
	}
	
	Bouton(SDL_Renderer* r, SDL_Texture* im, SDL_Texture* imd, std::function<void()> f, int anchorx, int anchory, int width, int height)
		:ObjetGraphique(r, im,anchorx, anchory, width, height), actionFunction(f),imageDown(imd)
	{ 
		clickable = true; type = BOUTON;
	}

	//Destructeur
	~Bouton() override {
		delete zone;
	}

	//Fonction d'affichage

	void render() override{
		if (visible) {
			SDL_RenderCopy(renderer, image, NULL, zone);
		}
	}
	
	void callback(const SDL_Event& e) override
	{
		
		switch (e.type) {
		case SDL_MOUSEBUTTONDOWN:
			SDL_Texture* tmp = image;
			if (imageDown != nullptr) image = imageDown;
			render();
			SDL_RenderPresent(renderer);
			SDL_Delay(150);
			image = tmp;
			actionFunction();
			break;
		}

		
	}

	void makeVisible() override
	{
		clickable = true;
		visible = true;
	}

	void makeInvisible() override
	{
		clickable = false;
		visible = false;
	}
};
