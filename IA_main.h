#ifndef IA_MAIN_H_INCLUDED
#define IA_MAIN_H_INCLUDED

#include "Damier.h"
#include "Othello.h"
#include "TranspositionTable.h"
#define MAXI 2147483647
#define MINI -2147483648

int maxi(int a,int b);
int mini(int a,int b);

/**
  *@brief permet d'evaluer la valeur d'une position
  *@return valeur de la position
*/
int heuristique(Damier* _damier,int joueur);

/**
  *@brief algorithme alpha-beta avec memoire
  *@param randvals sont la pour initialiser la fonction de hashage
          ttable est une table de transposition
          _damier est la racine de l'arbre
          prof est la profondeur max a evaluer dans l'arbre
          alpha est un minorant de la valeur
          beta est un majorant de la valeur
          maxnode permet de differencier noeuds min et max (pas d'implementation Negamax)
  *@return valeur strategique de la racine
*/
int alphaBeta(int randvals[8][8][2],Table* ttable,Damier* _damier,int joueur,char prof,int alpha,int beta,bool maxnode=true);

/**
  *@brief identique a alphabeta sauf pour le return
  *@param randvals sont la pour initialiser la fonction de hashage
          ttable est une table de transposition
          _damier est la racine de l'arbre
          prof est la profondeur max a evaluer dans l'arbre
  *@return le meilleur coup possible depuis la position sous la forme i*10+j avec i numero de ligne et j de colonne
*/
int joueCoupIA(int randvals[8][8][2],Table* ttable,Damier* _damier,int joueur,char prof);
void eXe();
#endif // IA_MAIN_H_INCLUDED




