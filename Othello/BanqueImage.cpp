#include "BanqueImage.h"
#ifndef WIN32
#include <unistd.h>
#endif

BanqueImage::BanqueImage(SDL_Renderer* rend)
{
	images = new std::map<std::string,SDL_Texture*>();
	renderer = rend;


	char* source = new char[1000];
#ifdef WIN32
	GetCurrentDirectoryA(1000, source);
#endif
#ifndef WIN32
	getcwd(source);
#endif
	std::string repertoireImages = std::string(source) + std::string("/images/");
	DIR * rep = opendir(repertoireImages.c_str());


	if (rep == NULL) {
		std::cerr << "cannot open : " << repertoireImages.c_str() << std::endl;

	}
	else {
		struct dirent* file = NULL;
		std::string nom;
		while ((file = readdir(rep)) != NULL) {
			//////////ajouter des images ici si besoin////////////////////////
			nom = std::string(file->d_name);
			try {
				nom = nom.substr(0, nom.find_first_of('.'));
				ajouteImage(nom, file->d_name);
			}
			catch (const char* e) {
				puts(e);
			}
			
		}
	}
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
		 
		 SDL_Surface* im = SDL_LoadBMP( (std::string("images/")+fichier).c_str());
		 
		 puts(SDL_GetError());
		 if (im != NULL) {
			 puts(nom.c_str());
			 (*images)[nom] = SDL_CreateTextureFromSurface(renderer, im);
			 puts(SDL_GetError());
		 }
		 SDL_FreeSurface(im);

		 return (*images)[nom];
	 }

	 return nullptr;	
}

///============================================

SDL_Texture* BanqueImage::getImage(const std::string& nom) {
	return (*images)[nom];
}
