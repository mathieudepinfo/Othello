#ifndef IA_ABTT_H_INCLUDED
#define IA_ABTT_H_INCLUDED

#include "IA_main.h"

/**
 * @brief fonction qui retourne la valeur d'un état,version améliorée de alphabeta qui utilise une table de transposition
 * @param Table& ttable est la table de transposition
 * @param Damier& damier est l'état initial à évaluer
 * @param int joueur est le joueur qui joue le prochain coup
 * @param char prof est la profondeur maximale jusqu'à laquelle explorer
 * @param int alpha est la borne minimale de l'état
 * @param int beta est la borne maximale de l'état
 * @param bool maxnode qui est vrai si on doit maximiser le score
 * @return un entier qui correspond à la valeur de l'état selon une heuristique donnée
 */
int alphaBetaTT(Table& ttable,Damier& damier,int joueur,char prof,int alpha,int beta,bool maxnode=true);

#endif // IA_ABTT_H_INCLUDED
