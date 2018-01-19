#pragma once

///================Fichier contenant l'algorithme MTD-f==========================

#include "IA_main.h"
#include "IA_abTT.h"
#include <time.h>
/**
 *@brief algorithme MTD-f, alpha-betaTT avec fenètre nulle, renvoie une exception si le temps est écoulé avant la fin du calcul
 *@param f l'estimation initiale de la position
 *@param ttable une table de transposition
 *@param root le damier initial
 *@param joueur le joueur maximisant
 *@param prof la profondeur maximale
 *@param tmax
 *@param t0
 */
int MTD(int& f,Table& ttable,const Damier& root,int joueur,char prof,int& coup,int (*heuristique)(const Damier&,int),time_t tmax,time_t t0);

