#ifndef IA_MAIN_H_INCLUDED
#define IA_MAIN_H_INCLUDED

#include "Damier.h"
#include "Othello.h"
#include "TranspositionTable.h"
#include <stdio.h>
#include <assert.h>

inline int maxi(int a,int b){

    return (a>b)? a:b;
}
inline int mini(int a,int b){

    return (a<b)? a:b;
}

/**
 * @brief met toutes les possibilités de jeu pour jouer dans les n_coups premières cases de coups
 * @param int coups[64][2] paramètre modifié,liste des coups possible
 * @param Damier& damier état actuel
 * @param int& n_coups entier qui contient le nombre de coups possibles
 * @param int joueur
 */
void possibilites(int coups[64][2],Damier& damier,int& n_coups,int joueur);

bool inList(int i,int j,int coups[64][2],int n_coups);

/**
 *
 */
void possibilites(int coups[64][2],Damier& damier,int& n_coups,int joueur,Table& ttable, unsigned int cle);

/**
  *@brief permet d'evaluer la valeur d'une position
  *@param Damier& damier la position à évaluer
  *@param int joueur
  *@return valeur de la position
*/
int heuristique(Damier& damier,int joueur);

#endif // IA_MAIN_H_INCLUDED




