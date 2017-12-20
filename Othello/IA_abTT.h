#pragma once

///================Fichier contenant l'algorithme Alpha Beta avec mémoire==========================

#include "IA_main.h"
#include <time.h>

/**
 * @brief fonction qui retourne la valeur d'un état,version améliorée de alphabeta qui utilise une table de transposition
 * @param ttable est la table de transposition
 * @param damier est l'état initial à évaluer
 * @param joueur est le joueur qui joue le prochain coup
 * @param prof est la profondeur maximale jusqu'à laquelle explorer
 * @param alpha est la borne minimale de l'état
 * @param beta est la borne maximale de l'état
 * @param maxnode qui est vrai si on doit maximiser le score
 * @param heuristique la fonction d'évalluation à utiliser
 * @return un entier qui correspond à la valeur de l'état selon une heuristique donnée
 */
int alphaBetaTT(Table& ttable,Damier& damier,int joueur,char prof,int alpha,int beta,int& coup,int (*heuristique)(Damier&,int), time_t tmax, time_t t0, bool maxnode = true);

