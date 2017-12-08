#pragma once

///====================================Classe MenuPrincipal====================

#include "SDL.h"
#include <vector>

#include "Bouton.h"
#include "BanqueImage.h"
#include "Plateau.h"

/**
 * Classe qui repr�sente notre fen�tre graphique, elle recevra les events et chosira les actions � effectuer
 * Elle contient :
 * -une liste des ObjetGraphique la composant
 * -une banque d'image
 * -une SDL_Window
 * -un SDL_Renderer
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
	
	/**
	 * Fonction statique qui permet de n'avoir qu'une instance de la classe au maximum
	 */
	static MenuPrincipal* getInstance() {
		static MenuPrincipal* menu=new MenuPrincipal();
		return menu;
	}

	~MenuPrincipal();

	void actualise();

	void addItem(ObjetGraphique* obj);

	ObjetGraphique* getObjectOnMouseClick(SDL_Event& event);

	SDL_Texture* getTexture(std::string name);

	BanqueImage* getBanque() {
		return banque;
	}
};
