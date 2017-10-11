#ifndef DAMIER
#define DAMIER
#include <iostream>

class Damier
{
    public:

    int cases[8][8];

    Damier(int setup[8][8]);

    /**
    *@param i numero de ligne, j numero de colonne
    *@return cases[i][j]
    */
    int getV(int i,int j);

    /**
    *@param new_val nouvelle valeur, i numero de ligne, j numero de colonne
    */
    void setV(int new_val,int i,int j);

    /**
    *@brief affiche le damier en console
    */
    void affiche();


};

#endif // DAMIER
