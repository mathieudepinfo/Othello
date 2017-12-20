#pragma once

///====================================Classe MenuPrincipal====================

#include "SDL.h"

#include <vector>
#include <stdarg.h>

#include "ObjetGraphique.h"
#include "BanqueImage.h"
#include "Bouton.h"

#include "Plateau.h"

/**
 * Classe qui repr�sente notre fen�tre graphique, elle recevra les events et chosira les actions � effectuer
 * Elle contient :
 * -une liste des ObjetGraphique la composant
 * -une banque d'image
 * -une SDL_Window
 * -un SDL_Renderer
 * -une police de caract�res
 */
class MenuPrincipal
{
protected:

	std::vector<ObjetGraphique*>* items;
	BanqueImage* banque;
	SDL_Window* fenetre;
	SDL_Renderer* renderer;


	MenuPrincipal();

public:
	
	ObjetGraphique* focusedObject;

	/**
	 * Fonction statique qui permet de n'avoir qu'une instance de la classe au maximum
	 */
	static MenuPrincipal* getInstance() {
		static MenuPrincipal* menu=new MenuPrincipal();
		return menu;
	}

	~MenuPrincipal();

	/**
	 * Fonction appel�e d�s qu'un event est re�u 
	 */
	void onEvent(SDL_Event& e);

	/**
	 * Fonction d'affichage qui affiche tous les "items"
	 */
	void render();

	/*ajoute obj � items*/
	void addItem(ObjetGraphique* obj);

	/*ajoute plusieurs items*/
	void addItems(int nombreItems,...);

	/*Permet de r�cuperer l'objet concern� par l'event */
	ObjetGraphique* getObjectOnEvent(SDL_Event& event);

	/*Fonction d'acc�s � la banque d'images*/
	SDL_Texture* getTexture(std::string name);

	/*Foncion d'affichage du focus prend la forme d'un contour jaune*/
	void renderFocus();

	BanqueImage* getBanque() {
		return banque;
	}

	SDL_Renderer* getRenderer() {
		return renderer;
	}
};

