#ifndef IA_AB_H_INCLUDED
#define IA_AB_H_INCLUDED
#include "Damier.h"
#include "Othello.h"
#include "IA_main.h"

int alphaBeta2(Damier* _damier,int joueur,char prof,int alpha,int beta,bool maxnode=true);
int joueCoupIA2(Damier* _damier,int joueur,char prof);

#endif // IA_AB_H_INCLUDED
