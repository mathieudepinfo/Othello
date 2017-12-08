#include "BanqueImage.h"
#include <iostream>
#include <map>

BanqueImage::BanqueImage(SDL_Renderer* renderer)
{
	this->images = new std::map<std::string,SDL_Texture*>();
	this->renderer = renderer;

	//////////ajouter des images ici si besoin////////////////////////
	this->ajouteImage(std:: string("plateau"),		std::string("Plateau.bmp"));
	this->ajouteImage(std::string("boutonIAVSIA"),	std::string("BoutonIAVSIA.bmp"));
	this->ajouteImage(std::string("boutonJVJ"),		std::string("BoutonJVJ.bmp"));
	this->ajouteImage(std::string("boutonJVSIA"),	std::string("BoutonJVSIA.bmp"));
	this->ajouteImage(std::string("boutonFacile"),	std::string("BoutonFacile.bmp"));
	this->ajouteImage(std::string("boutonMoyen"),	std::string("BoutonMoyen.bmp"));
	this->ajouteImage(std::string("boutonDur"),		std::string("BoutonDur.bmp"));
	this->ajouteImage(std::string("pionBlanc"),		std::string("pionBlanc.bmp"));
	this->ajouteImage(std::string("pionNoir"),		std::string("pionNoir.bmp"));
	this->ajouteImage(std::string("possible"),		std::string("possible.bmp"));
	this->ajouteImage(std::string("vide"),			std::string("vide.bmp"));
	this->ajouteImage(std::string("mentor"),		std::string("mentor.bmp"));
}

///============================================

BanqueImage::~BanqueImage()
{
	for (std::string nom : names) {

		SDL_DestroyTexture((*images)[nom]);
	}

	delete images;
	
}

///============================================

 SDL_Texture* BanqueImage::ajouteImage(std::string nom,std::string fichier) {
	
	 if (find(names.begin(), names.end(), nom) == names.end()) { //si l'image n'est pas déja chargée
		 names.push_back(nom);
		 std::cout << "Load in bank : " << fichier.c_str()<<std::endl;
		 SDL_Surface* im = SDL_LoadBMP(fichier.c_str());
		 (*images)[nom] = SDL_CreateTextureFromSurface(renderer,im);
		 SDL_FreeSurface(im);

		 return (*images)[nom];
	 }

	 return nullptr;	
}

///============================================

SDL_Texture* BanqueImage::getImage(std::string nom) {
	return (*images)[nom];
}
