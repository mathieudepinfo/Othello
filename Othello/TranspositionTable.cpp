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
{
    this->distance=UNDEF;
    this->nbasse=MAXI;
    this->nhaute=MINI;
    this->real_key=UNDEF;
    this->mc=UNDEF;
}

Table::Noeud::Noeud(const Noeud& ni)
{
    this->distance=ni.getD();
    this->nbasse=ni.getL();
    this->nhaute=ni.getU();
    this->real_key=ni.getK();
	this->mc = ni.getC();
	
}

///=======================================================

void Table::store(unsigned int cle,unsigned int lcle,char prof,short meilleurcoup,int val,char flag){

    (*this)[cle]->setK(lcle);
    (*this)[cle]->setD(prof);
	(*this)[cle]->setC(meilleurcoup);

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

unsigned int hashage(Damier& damier,int joueur)
{
    //seeds utilisées pour le hashage (type Zobrist), tableau symétrique par rotation de 90degrés
    static unsigned int seeds[8][8][2]=
    {
        {{1656079727,610232524},{125089092,1628998920},{1703760725,882565151},{1639394878,297003772},{1639394878,297003772},{1703760725,882565151},{125089092,1628998920},{1656079727,610232524}},
        {{2040827370,1777021370},{1711502556,270090525},{509792504,1696582105},{1268973679,26043505},{1268973679,26043505},{509792504,1696582105},{1711502556,270090525},{2040827370,1777021370}},
        {{649878854,219511193},{1772825616,1068657239},{1328008765,1775057571},{145143634,1494748382},{145143634,1494748382},{1328008765,1775057571},{1772825616,1068657239},{649878854,219511193}},
        {{428033047,1053798443},{1511077093,270634401},{272207812,595093729},{921752792,1928287539},{921752792,1928287539},{272207812,595093729},{1511077093,270634401},{428033047,1053798443}},
        {{428033047,1053798443},{1511077093,270634401},{272207812,595093729},{921752792,1928287539},{921752792,1928287539},{272207812,595093729},{1511077093,270634401},{428033047,1053798443}},
        {{649878854,219511193},{1772825616,1068657239},{1328008765,1775057571},{145143634,1494748382},{145143634,1494748382},{1328008765,1775057571},{1772825616,1068657239},{649878854,219511193}},
        {{2040827370,1777021370},{1711502556,270090525},{509792504,1696582105},{1268973679,26043505},{1268973679,26043505},{509792504,1696582105},{1711502556,270090525},{2040827370,1777021370}},
        {{1656079727,610232524},{125089092,1628998920},{1703760725,882565151},{1639394878,297003772},{1639394878,297003772},{1703760725,882565151},{125089092,1628998920},{1656079727,610232524}},
    };

    unsigned int res=0;

    for(int i(0);i<8;i++){
        for(int j(0);j<8;j++){
            if(damier.getV(i,j)!=0){
                //xor sur les positions
                res=res^(seeds[i][j][damier.getV(i,j)]);
            }
        }
    }
    res=res^joueur;
    return res;
}



