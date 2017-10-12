#include "IA_main.h"
#include <stdio.h>

using namespace std;

int maxi(int a,int b){

    if(a<=b){
        return b;
    }
    else{
        return a;
    }
}

int mini(int a,int b){

    if(a<=b){
        return a;
    }
    else{
        return b;
    }
}

int heuristique(Damier* _damier,int joueur)
{

    int score(0);
    if(_damier->nbpion<50){
        int points[8][8]={
            { 500 ,-150, 30, 10, 10, 30,-150, 500},
            {-150 ,-250,  0,  0,  0,  0,-250,-150},
            { 30  ,  0 ,  1,  2,  2,  1,  0 , 30 },
            { 10  ,  0 ,  2, 16, 16,  2,  0 , 10 },
            { 10  ,  0 ,  2, 16, 16,  2,  0 , 10 },
            { 30  ,  0 ,  1,  2,  2,  1,  0 , 30 },
            {-150 ,-250,  0,  0,  0,  0,-250,-150},
            { 500 ,-150, 30, 10, 10, 30,-150, 500}
            };

        //controlecoin
        if(_damier->cases[0][0]==joueur){
            points[0][1]=50;points[1][0]=50;points[1][1]=0;points[0][2]=10;points[2][0]=10;
        }
        else if(_damier->cases[0][0]==3-joueur){
            points[0][1]=10;points[1][0]=10;points[1][1]=0;points[0][2]=10;points[2][0]=10;
        }
        if(_damier->cases[7][0]==joueur){
            points[7][1]=50;points[6][0]=50;points[6][1]=0;points[7][2]=10;points[5][0]=10;
        }
        else if(_damier->cases[7][0]==3-joueur){
            points[7][1]=10;points[6][0]=10;points[6][1]=0;points[7][2]=10;points[5][0]=10;
        }
        if(_damier->cases[7][7]==joueur){
            points[7][6]=50;points[6][7]=50;points[6][6]=0;points[5][7]=10;points[7][5]=10;
        }
        else if(_damier->cases[7][7]==3-joueur){
            points[7][6]=10;points[6][7]=10;points[6][6]=0;points[5][7]=10;points[7][5]=10;
        }
        if(_damier->cases[0][7]==joueur){
            points[0][6]=50;points[1][7]=50;points[1][6]=0;points[5][0]=10;points[2][7]=10;
        }
        else if(_damier->cases[0][7]==3-joueur){
            points[0][6]=10;points[1][7]=10;points[1][6]=0;points[5][0]=10;points[2][7]=10;
        }

        //mobilite + calcul du score
        for(int i(0);i<8;i++){
            for(int j(0);j<8;j++){
                if(_damier->cases[i][j]==joueur){
                    score+=points[i][j];
                    score-=_damier->contigues[i][j];
                }
                else{
                    score-=points[i][j];
                }
            }
        }

    }
    else{
        for(int i(0);i<8;i++){
            for(int j(0);j<8;j++){
                if(_damier->cases[i][j]==joueur){
                    score+=1;
                }

            }
        }
    }
    return score;
}

int alphaBeta(Table* ttable,Damier* _damier,int joueur,char prof,int alpha,int beta,bool maxnode)
{
    int val;//valeur du noeud

    //on regarde si le noeud est dans la table
    unsigned int lcle=hashage(_damier);
    unsigned short cle=static_cast<unsigned short>(lcle);

    if(   ttable->hashtable[cle]->distance!=255
       && ttable->hashtable[cle]->real_key==lcle){

        Noeud* n=ttable->hashtable[cle];
        //si la valeur de la table est valable a la profondeur actuelle
        if(n->distance>=prof){ //en fait cette condition est peu utile car le nombre de pions est strictement croissant

            if(n->vbasse>=beta){return n->vbasse;}
            if(n->vhaute<=alpha){return n->vhaute;}
            alpha=maxi(alpha,n->vbasse);
            beta=mini(beta,n->vhaute);
        }
    }
    //si on est sur un noeud terminal
    if(prof==0 || testFin(_damier)){
        return heuristique(_damier,joueur);
    }

    if(maxnode){

        val=MINI;
        //on parcours tout les coups valides
        for(int i(-1);i<8;i++){
            for(int j(0);j<8;j++){//pas optimal

                if(estValide(_damier,joueur,i,j)){

                    if(val<beta){
                        Damier* fils=new Damier(_damier->cases,_damier->contigues);
                        joueCoup(fils,joueur,i,j);
                        val=maxi(val,alphaBeta(ttable,fils,joueur,prof-1,alpha,beta,false));
                        alpha=maxi(alpha,val);
                        delete fils;
                    }
                    else{//elagage beta
                        i=8;
                        j=8;
                        //on met a jour notre table
                        ttable->hashtable[cle]->real_key=lcle;
                        ttable->hashtable[cle]->vhaute=val;
                        ttable->hashtable[cle]->distance=prof;
                    }

                }
            }
        }

    }
    else{ //noeud min code similaire a maxnode

        val=MAXI;

        for(int i(-1);i<8;i++){
            for(int j(0);j<8;j++){//pas optimal

                if(estValide(_damier,3-joueur,i,j)){

                    if(val>alpha){
                        Damier* fils=new Damier(_damier->cases,_damier->contigues);
                        joueCoup(fils,3-joueur,i,j);
                        val=mini(val,alphaBeta(ttable,fils,joueur,prof-1,alpha,beta,true));
                        beta=mini(val,beta);
                        delete fils;
                    }
                    else{
                        i=8;
                        j=8;
                        ttable->hashtable[cle]->real_key=lcle;
                        ttable->hashtable[cle]->vbasse=val;
                        ttable->hashtable[cle]->distance=prof;
                    }
                }
            }
        }
    }
    //si notre valeur a ete calculee jusqu au bout -> maj de la table
    if(val>alpha && val<beta){

        ttable->hashtable[cle]->vbasse=val;
        ttable->hashtable[cle]->vhaute=val;
        ttable->hashtable[cle]->distance=prof;
        ttable->hashtable[cle]->real_key=lcle;
    }

    return val;
}

int joueCoupIA(Table* ttable,Damier* _damier,int joueur,char prof)
{
//fonction similaire a un maxnode mais on stocke aussi le meilleurcoup
    int vmax(MINI),val(MINI);
    int alpha(MINI),beta(MAXI);
    int meilleurcoup=-2; //valeur impossible

    unsigned int lcle=hashage(_damier);
    unsigned short cle=static_cast<unsigned short>(lcle);

    if(   ttable->isIn(cle)!=NULL
       && ttable->hashtable[cle]->real_key==lcle){

        Noeud* n=ttable->hashtable[cle];
        if(n->distance>=prof){
            if(n->vbasse>=beta){return n->vbasse;}
            if(n->vhaute<=alpha){return n->vhaute;}
            alpha=maxi(alpha,n->vbasse);
            beta=mini(beta,n->vhaute);
        }
    }

    for(int i(-1);i<8;i++){
        for(int j(0);j<8;j++){

            if(estValide(_damier,joueur,i,j)){

                if(val<beta){
                    Damier* fils=new Damier(_damier->cases,_damier->contigues);
                    joueCoup(fils,joueur,i,j);
                    val=alphaBeta(ttable,fils,joueur,prof-1,alpha,beta,false);
                    //cette fois on stocke le coup
                    if(val>vmax){
                        vmax=val;
                        meilleurcoup=i*10+j;
                    }
                    alpha=maxi(alpha,vmax);
                    delete fils;
                }
                else{
                    i=8;
                    j=8;
                    ttable->hashtable[cle]->real_key=lcle;
                    ttable->hashtable[cle]->vbasse=val;
                    ttable->hashtable[cle]->distance=prof;
                }

            }
        }
    }
    if(val>alpha && val<beta){

        ttable->hashtable[cle]->vbasse=val;
        ttable->hashtable[cle]->vhaute=val;
        ttable->hashtable[cle]->distance=prof;
        ttable->hashtable[cle]->real_key=lcle;
    }

    return meilleurcoup;
}


