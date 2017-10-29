#ifndef DAMIER
#define DAMIER
#include <iostream>

class Damier
{
    private:

    int contigues[8][8];
    int cases[8][8];
    int nbpion=0;

    public:

    void init(Damier* damier,const int setup[8][8],const int cont[8][8]);

    Damier(const int setup[8][8],const int cont[8][8]);

    Damier(const Damier &damier);

    /**
    *@param i numero de ligne, j numero de colonne
    *@return cases[i][j]
    */
    int getV(int i,int j){
        return cases[i][j];
    }

    int getC(int i,int j){
        return contigues[i][j];
    }

    int getNp(){
        return nbpion;
    }

    void iNp(){
        nbpion++;
    }
    /**
    *@param new_val nouvelle valeur, i numero de ligne, j numero de colonne
    */
    void setV(int new_val,int i,int j){
        cases[i][j]=new_val;
    }

    void setC(int new_val,int i,int j){
        contigues[i][j]=new_val;
    }

    void Cminus(int i,int j,int diff){
        contigues[i][j]-=diff;
    }
    /**
    *@brief affiche le damier en console
    */

    void affiche();


};

#endif // DAMIER
