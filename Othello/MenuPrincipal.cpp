#include "MenuPrincipal.h"

///=========================================

MenuPrincipal::MenuPrincipal()
{
	//création de la fenetre
	fenetre = SDL_CreateWindow("Othello", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000, 800, SDL_WINDOW_SHOWN);
	//création du renderer
	renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//création de la banque d'image
	banque = new BanqueImage(renderer); 

	items = new std::vector<ObjetGraphique*>();
	
}

///=========================================

MenuPrincipal::~MenuPrincipal()
{
	delete banque;
	for (auto ob : *items) {
		delete ob;
	}
	delete items;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(fenetre);

}

///=========================================

void MenuPrincipal::actualise() {
	//on nettoie le renderer
	SDL_RenderClear(renderer);

	//on copie tout les objets dans le renderer
	for (auto obj : *items) {
		obj->render(renderer);
	}

	renderFocus();

	//on affiche le résultat
	SDL_RenderPresent(renderer);
}

///=========================================

void MenuPrincipal::addItem(ObjetGraphique * obj)
{
	items->push_back(obj);
}

///=========================================

ObjetGraphique* MenuPrincipal::getObjectOnMouseClick(SDL_Event& event) {

	//on récupère les coordonnées du click
	int x = event.button.x;
	int y = event.button.y;

	//on choisis le bon objet
	for (auto obj : *items) {
		if (obj->clickable) {//on ne peut retourner que les objets clickable
			if (obj->isInZone(x, y)) {
				//si un objet prend le focus on l'indique
				if(event.type == SDL_MOUSEBUTTONUP) focusedObject = obj;
				return obj;
			}
		}
	}

	return nullptr;
}

///=========================================

SDL_Texture * MenuPrincipal::getTexture(std::string name)
{
	return banque->getImage(name);
}

void MenuPrincipal::renderFocus() {

	if (focusedObject == nullptr) return;

	SDL_Rect* zone = focusedObject->getZone();

	//couleur jaune
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);

	//on dessine un rectangle autour de la zone de l'objet 
	SDL_RenderDrawLine(renderer, zone->x, zone->y, zone->x + zone->w,zone->y);
	SDL_RenderDrawLine(renderer, zone->x+zone->w, zone->y, zone->x + zone->w, zone->y+zone->h);
	SDL_RenderDrawLine(renderer, zone->x+zone->w, zone->y+zone->h, zone->x, zone->y+zone->h);
	SDL_RenderDrawLine(renderer, zone->x, zone->y+zone->h, zone->x , zone->y);

	//on remet la couleur par défaut noire
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}