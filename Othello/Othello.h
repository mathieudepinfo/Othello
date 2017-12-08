#pragma once

///================Fichier contenant les fonctions principales pour le d�roulement d'une partie d'Othello==========================

#include "Damier.h"
#include <vector>

/**
  *@brief test la validite du coup a la position (k,l)
  *@param int k numero de ligne, -1 pour passer
  *@param int l numero de colonne
  *@return true si on peut jouer, false sinon
*/
bool estValide(Damier& damier,int joueur,int k,int l=0);

/**
 *@brief joue le coup a la position (k,l), le coup doit prealablement avoir ete teste avec estValide
 *@param int k numero de ligne -1 pour passer
 *@param int l numero de colonne
*/
void joueCoup(Damier& damier,int joueur, int k,int l=0);

/**
*@brief test si la partie est finie
*@return true si partie terminee,false sinon
*/
bool testFin(Damier& damier);

/**@brief retourne le nombre de pions de joueur sur Damier*/
int score(Damier& damier, int joueur);
