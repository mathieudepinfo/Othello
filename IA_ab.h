#ifndef IA_AB_H_INCLUDED
#define IA_AB_H_INCLUDED

#include "IA_main.h"
/**
 * @brief fonction qui retourne la valeur d'un état grace a l'algorithme alphabeta, meilleurcoup contient le meilleurcoup possible pour cet état
 * @param Damier& damier est l'état initial à évaluer
 * @param int joueur est le joueur qui joue le prochain coup
 * @param char prof est laz profondeur maximale jusqu'à laquelle explorer
 * @param int alpha est la borne minimale de l'état
 * @param int beta est la borne maximale de l'état
 * @param int& meilleurcoup réference vers un entier qui sera actualisé au meilleurcoup possible
 * @param bool maxnode qui est vrai si on doit maximiser le score
 * @return un entier qui correspond à la valeur de l'état selon une heuristique donnée
 */
int alphaBeta(Damier& damier,int joueur,char prof,int alpha,int beta,int& meilleurcoup,bool maxnode=true);

#endif // IA_AB_H_INCLUDED
