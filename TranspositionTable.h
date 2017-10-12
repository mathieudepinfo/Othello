#ifndef TRANSPOSITIONTABLE_H_INCLUDED
#define TRANSPOSITIONTABLE_H_INCLUDED

#include "Damier.h"
#define MAXI 2147483647
#define MINI -2147483648

class Noeud
{
    public:

    Noeud(char distance,int vhaute, int vbasse);
    char distance;//profondeur au moment de l'enregistrement
    int vhaute;//borne superieure du noeud
    int vbasse;//borne inferieure du noeud
    unsigned int real_key;//cle de hashage reelle sur 32bits
};

class Table
{
    public:

    Table();
    ~Table();
    Noeud** hashtable;

    /**
      *@brief permet de savoir si la cle est dans la table
      *@return NULL si non , le Noeud* present si oui
    */
    Noeud* isIn(unsigned short cle);

};

/**
  *@brief fonction de hashage de type Zobrist
  *@param _damier est la position à hasher
*/
unsigned int hashage(Damier* _damier);
#endif // TRANSPOSITIONTABLE_H_INCLUDED
