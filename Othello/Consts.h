#pragma once

///====================Fichier contenant les constantes==================

constexpr int MAXI = 2147483647;
constexpr int MINI = -2147483647;

//types de parties
enum { IAVSIA = 0, JVSIA = 1, JVJ = 2 };

//différents types d'objets
enum {
	BOUTON = 1, PLATEAU = 2, BOUTON_NIVEAU = 3, BOUTON_START = 4, BOUTON_JOUEUR = 5, BOUTON_RETOUR=6
};

//valeurs des cases du plateau
enum{POSSIBLE=10, MENTOR=5, NOIR=2, BLANC=1, VIDE=0,RETOURNEMENT=20};


//taille des tables de transposition 
constexpr int TABLE_SIZE = 65536;

//valeur de départ d'une partie
constexpr int JOUEUR_INITIAL = 2;
constexpr int DAMIER_INITIAL[8][8] =
{
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,2,0,0,0 },
	{ 0,0,0,2,1,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0 },
};