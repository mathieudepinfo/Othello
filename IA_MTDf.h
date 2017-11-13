#ifndef IA_MTDF_H_INCLUDED
#define IA_MTDF_H_INCLUDED

#include "IA_main.h"
#include "IA_abTT.h"
/**
 *@brief algorithme MTD-f, alpha-betaTT avec fenètre nulle, renvoie une exception si le temps est écoulé avant la fin du calcul
 *@param int& f l'estimation initiale de la position
 *@param Tabble& ttable une table de transposition
 *@param Damier& root le damier initial
 *@param int joueur le joueur maximisant
 *@param char prof la profondeur maximale
 *@param time_t tmax
 *@param time_t t0
 */
int MTD(int& f,Table& ttable,Damier& root,int joueur,char prof,time_t tmax,time_t t0);

#endif // IA_MTDF_H_INCLUDED
