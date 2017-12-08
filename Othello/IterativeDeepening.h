#pragma once

///================Fichier contenant la fonction d'Iterative Deepening==========================

#include "IA_main.h"
#include "IA_MTDf.h"

/**
 *@brief Iterative deepening qui explore les profondeurs 1 à pmax s'il a le temps, sinon si tmax est atteint l'algo s'arrète
 *@param time_t tmax temps limite
 *@param char pmax profondeur maximale, utile en fin de partie
 *@param Damier& damier l'état actuel
 *@param Table& ttable une table de transposition
 *@param int joueur le joueur maximisant
 */
int ID(time_t tmax,char pmax,Damier& damier,Table& ttable,int joueur);

