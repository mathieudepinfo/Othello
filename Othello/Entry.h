#pragma once
#include "ObjetGraphique.h"
#include "SDL.h"
#include "SDL_ttf.h"

#include <string>

class Entry :
	public ObjetGraphique
{
public:
	Entry(SDL_Renderer* r,const std::string& nom, int x, int y, int width, int height);
	~Entry();

	void render() override;
	void callback(const SDL_Event& e)override;
	

};

class IntEntry :
	public Entry
{
private:
	int* myVar;
	std::string name;

public:
	IntEntry(SDL_Renderer* r, const std::string& nom, int* var, int x, int y, int width, int height):
		Entry(r, nom, x, y, width, height),name(nom),myVar(var);

	~IntEntry();


};