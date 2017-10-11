#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

#include "Damier.h"
#include "Othello.h"
#include <iostream>
#include <string>
#include "IA_main.h"
#include "TranspositionTable.h"
#include "IA_ab.h"
/**
  *@brief lance une partie joueur contre IA
  *@param player est le joueur humain(1 ou 2)
*/
void playerVSIA(int player);

/**
  *@brief lance une partie IA contre IA
*/
void IAVSIA();
#endif // PARTIE_H_INCLUDED
