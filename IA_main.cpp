#include "IA_main.h"
#include <stdio.h>

using namespace std;
void eXe(){}

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



    for(int i(0);i<8;i++){
        for(int j(0);j<8;j++){
            if(_damier->cases[i][j]==joueur){
                score+=points[i][j];
            }
            else{
                score-=points[i][j];
            }
        }
    }

    return score;
}

int alphaBeta(int randvals[8][8][2],Table* ttable,Damier* _damier,int joueur,char prof,int alpha,int beta,bool maxnode)
{
    int val;//valeur du noeud

    //on regarde si le noeud est dans la table
    unsigned int lcle=hashage(_damier,randvals);
    unsigned short cle=(unsigned short) lcle;

    if(   ttable->hashtable[cle]->distance!=255
       && ttable->hashtable[cle]->real_key==lcle){

        Noeud* n=ttable->hashtable[cle];
        //si la valeur de la table est valable a la profondeur actuelle
        if(n->distance>=prof){ //en fait ces tables sont peu utiles car le nombre de pions est strictement croissant

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
                        Damier* fils=new Damier(_damier->cases);
                        joueCoup(fils,joueur,i,j);
                        val=maxi(val,alphaBeta(randvals,ttable,fils,joueur,prof-1,alpha,beta,false));
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
                        Damier* fils=new Damier(_damier->cases);
                        joueCoup(fils,3-joueur,i,j);
                        val=mini(val,alphaBeta(randvals,ttable,fils,joueur,prof-1,alpha,beta,true));
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

int joueCoupIA(int randvals[8][8][2],Table* ttable,Damier* _damier,int joueur,char prof)
{
//fonction similaire a un maxnode mais on stocke aussi le meilleurcoup
    int vmax(MINI),val(MINI);
    int alpha(MINI),beta(MAXI);
    int meilleurcoup=-2; //valeur impossible

    unsigned int lcle=hashage(_damier,randvals);
    unsigned short cle=(unsigned short)lcle;

    if(   ttable->isIn((unsigned short)cle)!=NULL
       && ttable->hashtable[(unsigned short)cle]->real_key==lcle){

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
                    Damier* fils=new Damier(_damier->cases);
                    joueCoup(fils,joueur,i,j);
                    val=alphaBeta(randvals,ttable,fils,joueur,prof-1,alpha,beta,false);
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


