#include "TranspositionTable.h"

using namespace std;

Table::Table(int randvals[8][8][2]){

    hashtable=new Noeud*[65536];
    for(int i(0);i<65536;i++){
        //l'initialistation de distance à 255 permet de dire que le noeud est inexploré
        //(maximum 60coups dans une partie  => prof<=60
        hashtable[i]=new Noeud(255,MAXI,MINI);
    }

}

Noeud* Table::isIn(unsigned short cle){

    //si le noeud est inexplore
    if(hashtable[cle]->distance==255){
        return NULL;
    }
    else{

        return hashtable[cle];
    }
}

Noeud::Noeud(char d,int vh, int vb){

    distance=d;
    vhaute=vh;
    vbasse=vb;
    real_key=0;
}

unsigned int hashage(Damier* _damier,int randvals[8][8][2])
{
    unsigned int res=0;
    for(int i(0);i<8;i++){
        for(int j(0);j<8;j++){
            if(_damier->cases[i][j]!=0){
                //xor sur les positions permet de calculer les nouvelles cle facilement
                res=res^(randvals[i][j][_damier->cases[i][j]]);
            }

        }
    }

    return res;
}



