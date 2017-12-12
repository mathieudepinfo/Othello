#pragma once

///====================================Classe MenuPrincipal====================

#include "SDL.h"

#include <vector>

#include "ObjetGraphique.h"
#include "BanqueImage.h"
#include "Bouton.h"

#include "Plateau.h"

/**
 * Classe qui représente notre fenêtre graphique, elle recevra les events et chosira les actions à effectuer
 * Elle contient :
 * -une liste des ObjetGraphique la composant
 * -une banque d'image
 * -une SDL_Window
 * -un SDL_Renderer
 * -une police de caractères
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

	void actualise();

	void addItem(ObjetGraphique* obj);

	ObjetGraphique* getObjectOnMouseClick(SDL_Event& event);

	SDL_Texture* getTexture(std::string name);

	void renderFocus();

	BanqueImage* getBanque() {
		return banque;
	}

	SDL_Renderer* getRenderer() {
		return renderer;
	}
};

