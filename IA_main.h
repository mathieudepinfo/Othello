#ifndef IA_MAIN_H_INCLUDED
#define IA_MAIN_H_INCLUDED

#include "Damier.h"
#include "Othello.h"
#include "TranspositionTable.h"

inline int maxi(int a,int b){

    return (a>b)? a:b;
}
inline int mini(int a,int b){

    return (a<b)? a:b;
}


/**
  *@brief permet d'evaluer la valeur d'une position
  *@return valeur de la position
*/
int heuristique(Damier& damier,int joueur);

/**
  *@brief algorithme alpha-beta avec memoire
  *@param ttable est une table de transposition
          _damier est la racine de l'arbre
          prof est la profondeur max a evaluer dans l'arbre , Pinit la profondeur max
          coup sera mise a la valeur du meilleur coup sous la forme i*10+j
          alpha est un minorant de la valeur
          beta est un majorant de la valeur
          maxnode permet de differencier noeuds min et max (pas d'implementation Negamax)
  *@return valeur strategique de la racine
*/
int alphaBeta(Table& ttable,Damier& damier,int joueur,char prof,int alpha,int beta,bool maxnode=true);

/**
  *@brief identique a alphabeta sauf pour le return
  *@param ttable est une table de transposition
          _damier est la racine de l'arbre
          prof est la profondeur max a evaluer dans l'arbre
  *@return le meilleur coup possible depuis la position sous la forme i*10+j avec i numero de ligne et j de colonne
*/
#endif // IA_MAIN_H_INCLUDED




