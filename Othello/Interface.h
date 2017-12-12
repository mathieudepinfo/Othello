#pragma once

///===========================Fichier contenant des fonctions relatives � l'interface=========================

#include "SDL.h"

#include <iostream>
#include <vector>

#include "MenuPrincipal.h"
#include "Plateau.h"

#include "Damier.h"
#include "TranspositionTable.h"
#include "Othello.h"
#include "IA_ab.h"
#include "IterativeDeepening.h"

#include <vector>

class Plateau;
class MenuPrincipal;

/**
 *	Fonction qui sert � initialiser la SDL
 *  @return -1 si �chec, 0 sinon
 */
int initSDL();

/**
 * Fonction principale de l'interface qui permet de jouer un tour lors d'un click sur un plateau
 * @param fenetre est la fenetre qui contient le plateau
 * @param plateau est le plateau repr�sentant la partie
 * @param difficulte est la difficulte associ�e � l'IA
 * @param typePartie indique si l'on joue une partie JVJ ou JVSIA
 * @param i, j repr�sentent une case initiale sur laquelle jouer
 */
void joueTour(MenuPrincipal* fenetre, Plateau* plateau, int joueur,int difficulte, int typePartie, int i, int j);


/**
 * Lance une partie IAVSIA dans plateau
 */
void joueIAVSIA(MenuPrincipal* fenetre, Plateau* plateau, int difficulte);

/**
 * Fonction qui modifie coups pour contenir les pions qui seraient retourn�s si on joue en (k,l)
 * @param coups le param�tre modifi� qui contiendra les coups
 * @param dam le damier de jeu
 * @param joueur le joueur qui joue le coup
 * @param k,l la ligne et la colonne ou l'on souhaite jouer
 */
void getRetournements(std::vector<int>& coups,const Damier& dam, int joueur, int k, int l);