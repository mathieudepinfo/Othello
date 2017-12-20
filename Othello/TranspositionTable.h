#pragma once

///================Classe Table==========================

#include "Consts.h"
#include "Damier.h"
#include <vector>

constexpr unsigned long SEEDS[8][8][2] =
{
	{ { 1656079727,610232524 },{ 125089092,1628998920 },{ 1703760725,882565151 },{ 1639394878,297003772 },{ 1639394878,297003772 },{ 1703760725,882565151 },{ 125089092,1628998920 },{ 1656079727,610232524 } },
	{ { 2040827370,1777021370 },{ 1711502556,270090525 },{ 509792504,1696582105 },{ 1268973679,26043505 },{ 1268973679,26043505 },{ 509792504,1696582105 },{ 1711502556,270090525 },{ 2040827370,1777021370 } },
	{ { 649878854,219511193 },{ 1772825616,1068657239 },{ 1328008765,1775057571 },{ 145143634,1494748382 },{ 145143634,1494748382 },{ 1328008765,1775057571 },{ 1772825616,1068657239 },{ 649878854,219511193 } },
	{ { 428033047,1053798443 },{ 1511077093,270634401 },{ 272207812,595093729 },{ 921752792,1928287539 },{ 921752792,1928287539 },{ 272207812,595093729 },{ 1511077093,270634401 },{ 428033047,1053798443 } },
	{ { 428033047,1053798443 },{ 1511077093,270634401 },{ 272207812,595093729 },{ 921752792,1928287539 },{ 921752792,1928287539 },{ 272207812,595093729 },{ 1511077093,270634401 },{ 428033047,1053798443 } },
	{ { 649878854,219511193 },{ 1772825616,1068657239 },{ 1328008765,1775057571 },{ 145143634,1494748382 },{ 145143634,1494748382 },{ 1328008765,1775057571 },{ 1772825616,1068657239 },{ 649878854,219511193 } },
	{ { 2040827370,1777021370 },{ 1711502556,270090525 },{ 509792504,1696582105 },{ 1268973679,26043505 },{ 1268973679,26043505 },{ 509792504,1696582105 },{ 1711502556,270090525 },{ 2040827370,1777021370 } },
	{ { 1656079727,610232524 },{ 125089092,1628998920 },{ 1703760725,882565151 },{ 1639394878,297003772 },{ 1639394878,297003772 },{ 1703760725,882565151 },{ 125089092,1628998920 },{ 1656079727,610232524 } },
};

 /** Table représente une table de transposition.
  *  Une table sert à stocker des informations sur un Noeud
  *  Elle dispose de TABLE_SIZE places dans sa table de hashage.
  *  Elle ccontient aussi un tableau int presence[TABLE_SIZE] qui
  *  permet de savoir si le Noeud recherché a déja été exploré
  *  UNDEF sert à initialiser les valeurs
  */
class Table
{
	static const int UNDEF = -10;

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
	void operator=(const Table& table);
    
};

/**
  *@brief fonction de hashage de type Zobrist
  *@param Damier& damier est l'état à hasher
  *@param int joueur est le joueur qui doit joueur le prochain coup
  */
unsigned long hashage(Damier& damier,int joueur);

