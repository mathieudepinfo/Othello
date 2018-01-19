#include "stdafx.h"
#include "Entry.h"


Entry::Entry(std::string& name, )
{

}


Entry::~Entry()
{
}


IntEntry::IntEntry(SDL_Renderer* r, const std::string& nom, int& valeur, int x, int y, int width, int height) :
	Entry(r, nom, x, y, width, height) {
	myVar = valeur;
	name = nom;
}