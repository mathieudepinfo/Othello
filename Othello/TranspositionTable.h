#pragma once

///================Classe Table==========================

#include "Damier.h"
#include <vector>

const int MINI=-10000;
const int MAXI=10000;
const int TABLE_SIZE=65536;
const int UNDEF=-10;

 /** Table représente une table de transposition.
  *  Une table sert à stocker des informations sur un Noeud
  *  Elle dispose de TABLE_SIZE places dans sa table de hashage.
  *  Elle ccontient aussi un tableau int presence[TABLE_SIZE] qui
  *  permet de savoir si le Noeud recherché a déja été exploré
  */
class Table
{
protected:

    /**Un Noeud représente un élement de la table,
     * Les informations stockées dans le noeud sont:
     *  - char distance qui représente le nombre de tours de jeu restantsà explorer lors du stockage
     *  - int nbasse, int nhaute qui représentent les bornes alpha et beta au moment de l'enregistrement
     *  - unsigned int real_key qui represente la cle en 32bits réelle (avant le modulo)
     *  - short mc qui représente le meilleur coup possible pour le Noeud correspondant
     */
    class Noeud{

        protected:
            char distance;
            int nbasse,nhaute;
            unsigned int real_key;
            short mc;

        public:
            //constructeur par défaut
            Noeud();

            //constructeur de copie
            Noeud(const Noeud&);

            //fonctions "get" qui permet un accès au données mais pas la modification
            char getD()const{
                return distance;
            }
            int getL()const{
                return nbasse;
            }
            int getU()const{
                return nhaute;
            }
            unsigned int getK()const{
                return real_key;
            }
            short getC()const{
                return mc;
            }

            //fonctions "set" qui permettent la modification des données
            void setD(char dist){
                distance=dist;
            }
            void setL(int low){
                nbasse=low;
            }
            void setU(int up){
                nhaute=up;
            }
            void setK(unsigned int key){
                real_key=key;
            }
            void setC(short coup){
                mc=coup;
            }
			
    };

    Noeud** hashtable;
    bool* presence;

public:
    //constructeur par défaut
    Table();

    //constructeur de copie
    Table(const Table& table);

    //destructeur
    ~Table();

    /**
     * @brief méthode qui permet de stocker un état dans la table
     * @param unsigned int cle qui indique l'emplacement de stockage
     * @param unsigned int lcle qui represente le hachage réel de l'état
     * @param char prof qui sera stockée dans distance
     * @param int val qui est la valeur du noeud, en fonction de la coupure elle sera stockée dans nbasse ou nhaute
     * @param char flag indique le type de coupure, 'e' pour exact, 'u' pour upperbound, 'l' pour lowerbound
     */
	void store(unsigned int cle, unsigned int lcle, char prof, short meilleurcoup, int val, char flag);

	/**
	 * @brief retourn true si la valeur est stockee dans la table
	 */
    bool isIn(unsigned short cle) const{
        return presence[cle];
    }

    /**@brief Redéfinition de l'opérateur [],
     * attention cet opérateur n'est pas un membre constant
     * @param unsigned int cle
     * @return Un pointeur vers le Noeud correspondant
     */
    Noeud* operator[](unsigned int cle){
        return this->hashtable[cle];
    }

    /**@brief Redéfinition de l'opérateur =,
     * @param Table& table est la table de transposition à copier, elle n'est pas modifiée,
     * (elle n'est pas déclarée comme constante car l'opérateur [] lui est appliquée ce qui provoquerait une erreur)
     */
	void operator=(const Table& table) {
        for(int i=0;i<TABLE_SIZE;i++){
            (*this)[i]->setC(table.hashtable[i]->getC());
            (*this)[i]->setK(table.hashtable[i]->getK());
            (*this)[i]->setL(table.hashtable[i]->getL());
            (*this)[i]->setU(table.hashtable[i]->getU());
            (*this)[i]->setD(table.hashtable[i]->getD());
            (*this).presence[i]= table.isIn(i);
        }
    }
    
};

/**
  *@brief fonction de hashage de type Zobrist
  *@param Damier& damier est l'état à hasher
  *@param int joueur est le joueur qui doit joueur le prochain coup
  */
unsigned int hashage(Damier& damier,int joueur);

