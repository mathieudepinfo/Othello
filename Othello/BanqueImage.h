#pragma once

///====================================Fichier contenant la classe BanqueImage=================================

#include "SDL.h"

#include <map>
#include <vector>
#include <iostream>
#include "dirent.h"

/**
 * Classe qui contient toutes les images de l'interface (voir constructeur)
 * Attributs prives :
 * - renderer qui est le renderer des textures de la banque d'images
 * - images qui est un dictionnaire qui à un nom associe une texture
 * - names la listes des cles du dictionanaire
 */
class BanqueImage
{
private : 

	std::map<std::string,SDL_Texture*>* images;
	std::vector<std::string> names;
	SDL_Renderer* renderer;
	SDL_Texture* ajouteImage(std::string nom, std::string fichier);

public:

	//Constructeur
	BanqueImage(SDL_Renderer* renderer);

	//Destructeur
	~BanqueImage();

	//Membres get
	SDL_Texture* getImage(const std::string& nom);

	SDL_Renderer* getRenderer() {
		return renderer;
	}

};

