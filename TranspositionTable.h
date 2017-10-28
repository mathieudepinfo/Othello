#ifndef TRANSPOSITIONTABLE_H_INCLUDED
#define TRANSPOSITIONTABLE_H_INCLUDED

#include "Damier.h"

const int MINI=-2147483648;
const int MAXI=2147483647;
const int TABLE_SIZE=65536;

class Noeud{
    public:
        char distance;//profondeur au moment de l'enregistrement
        int vhaute;//borne superieure du noeud
        int vbasse;//borne inferieure du noeud
        unsigned int real_key;//cle de hashage reelle sur 32bits
        int mc;
        Noeud(char distance,int vhaute, int vbasse);

    };

class Table
{
private:

    Noeud** hashtable;



public:
    Table();
    ~Table();


    /**
      *@brief permet de savoir si la cle est dans la table
      *@return NULL si non , le Noeud* present si oui
    */
    Noeud* isIn(unsigned short cle){
        return ((*this)[cle]->distance==255)? NULL:(*this)[cle];
    }

    Noeud* operator[](unsigned short cle){
        return this->hashtable[cle];
    }
};

/**
  *@brief fonction de hashage de type Zobrist
  *@param _damier est la position à hasher
*/
unsigned int hashage(Damier* damier);
#endif // TRANSPOSITIONTABLE_H_INCLUDED
