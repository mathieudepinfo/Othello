#pragma once

///================Fichier contenant les fonctions principales pour le fonctionnement de l'IA==========================

#include "Damier.h"
#include "Othello.h"
#include "TranspositionTable.h"
#include "Consts.h"

#include <stdio.h>
#include <assert.h>
#include <vector>

inline int maxi(int a,int b){

    return (a>b)? a:b;
}
inline int mini(int a,int b){

    return (a<b)? a:b;
}

/**
 * @brief met toutes les possibilités de jeu pour jouer dans les n_coups premières cases de coups
 * @param coups paramètre modifié,liste des coups possible
 * @param damier état actuel
 * @param joueur le joueur qui est en train de jouer
 */
void possibilites(std::vector<int>& coups,const Damier& damier,int joueur);

/**
 * retourne true si {i,j} est dans coups
 */
bool inList(int i,int j,std::vector<int[2]>& coups);

/**
  *@brief permet d'evaluer la valeur d'une position
  *@param Damier& damier la position à évaluer
  *@param int joueur
  *@return valeur de la position
*/
int heuristiqueMilieuDePartie(const Damier& damier,int joueur);

int heuristiqueFinDePartie(const Damier& damier, int joueur);

int coefMobi(int nbPionTotal);



