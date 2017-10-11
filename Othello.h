#ifndef OTHELLO_H_INCLUDED
#define OTHELLO_H_INCLUDED

#include "Damier.h"
#include <vector>

/**
  *@brief test la validite du coup a la position (k,l)
  *@param k numero de ligne, -1 pour passer
          l numero de colonne
  *@return true si on peut jouer, false sinon
*/
bool estValide(Damier* _damier,int joueur,int k,int l=0);

/**
*@brief joue le coup a la position (k,l), le coup doit prealablement avoir ete teste avec estValide
*@param k numero de ligne -1 pour passer
        l numero de colonne
*/
void joueCoup(Damier* _damier,int joueur, int k,int l=0);

/**
*@brief test si la partie est finie
*@return true si partie terminee,false sinon
*/
bool testFin(Damier* _damier);

int score(Damier* _damier, int joueur);
#endif // OTHELLO_H_INCLUDED
