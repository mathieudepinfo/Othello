#include "TranspositionTable.h"

///==================Constructeurs Table==================

Table::Table()
{
    this->hashtable=new Noeud*[TABLE_SIZE];
    this->presence=new bool[TABLE_SIZE];

    for(int i(0);i<TABLE_SIZE;i++){

        this->hashtable[i]=new Noeud();
        this->presence[i]=0;
    }

}

Table::Table(const Table& table)
{
    this->hashtable=new Noeud*[TABLE_SIZE];
    this->presence=new bool[TABLE_SIZE];

    for(int i(0);i<TABLE_SIZE;i++){
        //on ne peut pas utiliser table[i] car table est const
		
		this->hashtable[i] = new Noeud(*(table.hashtable[i]));
        this->presence[i]=table.isIn(i);
    }
}

///==================Destructeur Table==================

Table::~Table()
{
    for(int i(0);i<TABLE_SIZE;i++){
        delete this->hashtable[i];
		
    }
    delete[] hashtable;
    delete[] presence;
}

///==================Constructeurs Noeud==================

Table::Noeud::Noeud() 
	:distance(UNDEF), nbasse(MAXI), nhaute(MINI), real_key(UNDEF), mc(UNDEF) {}

Table::Noeud::Noeud(const Noeud& ni)
	:distance(ni.getD()), nbasse(ni.getL()), nhaute(ni.getU()), real_key(ni.getK()), mc(ni.getC()) {}

///=======================================================

void Table::store(unsigned int cle,unsigned int lcle,char prof,short meilleurcoup,int val,char flag){

    (*this)[cle]->setK(lcle);
    (*this)[cle]->setD(prof);
	(*this)[cle]->setC(meilleurcoup);
	presence[cle] = true;

    switch(flag){
    case 'u':
        (*this)[cle]->setU(val);
        break;
    case 'l':
        (*this)[cle]->setL(val);
        break;
    case 'e':
        (*this)[cle]->setL(val);
        (*this)[cle]->setU(val);
        break;
    }
 }

///=======================================================

void Table::operator=(const Table& table) {
	for (int i = 0; i<TABLE_SIZE; i++) {
		(*this)[i]->setC(table.hashtable[i]->getC());
		(*this)[i]->setK(table.hashtable[i]->getK());
		(*this)[i]->setL(table.hashtable[i]->getL());
		(*this)[i]->setU(table.hashtable[i]->getU());
		(*this)[i]->setD(table.hashtable[i]->getD());
		(*this).presence[i] = table.isIn(i);
	}
}

///=======================================================

unsigned long hashage(const Damier& damier,int joueur)
{
    unsigned long res=0;

    for(int i(0);i<8;i++){
        for(int j(0);j<8;j++){
            if(damier.getV(i,j)!=0){
                //xor sur les positions
                res=res^(SEEDS[i][j][damier.getV(i,j)]);
            }
        }
    }
    res=res^joueur;
    return res;
}



