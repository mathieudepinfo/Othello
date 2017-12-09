#pragma once

///===========================Fichier contenant des fonctions relatives à l'interface=========================

#include <stdio.h>
#include <iostream>

#include "SDL.h"
#include "Partie.h"
#include "MenuPrincipal.h"

/**
 *	Fonction qui sert à initialiser la SDL
 *  @return -1 si échec, 0 sinon
 */
int initSDL();

/**
 * Fonction principale de l'interface qui permet de jouer un tour lors d'un click sur un plateau
 * @param fenetre est la fenetre qui contient le plateau
 * @param plateau est le plateau représentant la partie
 * @param difficulte est la difficulte associée à l'IA
 * @param typePartie indique si l'on joue une partie JVJ ou JVSIA
 * @param i, j représentent une case initiale sur laquelle jouer
 */
void joueTour(MenuPrincipal* fenetre, Plateau* plateau, int difficulte, int typePartie, int i, int j);

/**
 * Fonction lancée si il y a une partie dans le plateau lorsque l'in appuie sur "h" qui permet d'obenir l'aide de l'IA
 */
void mentor(Plateau* plateau);

/**
 * Lance une partie IAVSIA dans plateau
 */
void joueIAVSIA(MenuPrincipal* fenetre, Plateau* plateau, int difficulte);