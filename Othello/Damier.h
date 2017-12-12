#pragma once

///================Classe Damier==========================

#include <iostream>

/**Damier représente un plateau de jeu,
 * il possède un attribut int cases[8][8] qui représente l'état du damier
 * un damier sait toujours son nombre de pions actuels gràce a nbPions
 */
class Damier
{

private:

    int cases[8][8];
    int nbPions;
	long presence;
	long occupation;

public:
    /**
     * @brief initialise un damier passé en argument avec cases=setup
     * @param Damier* damier, un pointeur vers le damier à initialiser
     * @param int setup[8][8]
     */
    void init(Damier* damier,const int setup[8][8]);

    //constructeur à partir d'un setup
    Damier(const int setup[8][8]);

    //constructeur de copie
    Damier(const Damier &damier);

    //fonctions get, membres constants
    int getV(int i,int j)const{
        return cases[i][j];
    }

    int getNp()const{
        return nbPions;
    }

    /** méthode qui incrémente le nombre de pions */
    void iNp(){
        nbPions++;
    }

    /**
    *@param int new_val nouvelle valeur
    *@param int i numero de ligne
    *@param int j numero de colonne
    */
    void setV(int new_val,int i,int j){
        cases[i][j]=new_val;
    }

    /**
    *@brief affiche le damier en console
    */
    void affiche();

};


