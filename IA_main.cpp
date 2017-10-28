#include "IA_main.h"
#include <stdio.h>

using namespace std;

int heuristique(Damier* damier,int joueur)
{
    int s(0);
    if(damier->getNp()<50){
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
        if(damier->getV(0,0)==joueur){
            points[0][1]=50;points[1][0]=50;points[1][1]=0;points[0][2]=10;points[2][0]=10;

        }
        else if(damier->getV(0,0)==3-joueur){
            points[0][1]=10;points[1][0]=10;points[1][1]=0;points[0][2]=10;points[2][0]=10;
        }
        if(damier->getV(7,0)==joueur){
            points[7][1]=50;points[6][0]=50;points[6][1]=0;points[7][2]=10;points[5][0]=10;
        }
        else if(damier->getV(7,0)==3-joueur){
            points[7][1]=10;points[6][0]=10;points[6][1]=0;points[7][2]=10;points[5][0]=10;
        }
        if(damier->getV(7,7)==joueur){
            points[7][6]=50;points[6][7]=50;points[6][6]=0;points[5][7]=10;points[7][5]=10;
        }
        else if(damier->getV(7,7)==3-joueur){
            points[7][6]=10;points[6][7]=10;points[6][6]=0;points[5][7]=10;points[7][5]=10;
        }
        if(damier->getV(0,7)==joueur){
            points[0][6]=50;points[1][7]=50;points[1][6]=0;points[5][0]=10;points[2][7]=10;
        }
        else if(damier->getV(0,7)==3-joueur){
            points[0][6]=10;points[1][7]=10;points[1][6]=0;points[5][0]=10;points[2][7]=10;
        }

        //mobilite + calcul du score
        for(int i(0);i<8;i++){
            for(int j(0);j<8;j++){
                if(damier->getV(i,j)==joueur){
                    s+=points[i][j];
                    s-=damier->getC(i,j);
                }
                else if(damier->getV(i,j)==3-joueur){
                    s-=points[i][j];
                    s+=damier->getC(i,j);
                }
            }
        }

    }
    else{
        for(int i(0);i<8;i++){
            for(int j(0);j<8;j++){
                if(damier->getV(i,j)==joueur){
                    s+=1;
                }
            }
        }
    }
    return s;
}

int alphaBeta(Table* ttable,Damier* damier,int joueur,char prof,int alpha,int beta,bool maxnode)
{
    int val,v,meilleurcoup;
    //printf("ici1\n");
    //on regarde si le noeud est dans la table
    unsigned int lcle=hashage(damier);
    unsigned short cle=static_cast<unsigned short>(lcle);

    //printf("ici2 %d %d\n",prof,cle);
    //printf("ici2 %p %d\n",(*ttable)[0],0);

    if(   (*ttable)[cle]->distance!=255
       && (*ttable)[cle]->real_key==lcle){
        //printf("bas\n");
        Noeud* n=(*ttable)[cle];
        //si la valeur de la table est valable a la profondeur actuelle
        if(n->distance>=prof){ //en fait cette condition n'est pas une inegalité car le nombre de pions est strictement croissant

            if(n->vbasse>=beta){
                return n->vbasse;
            }
            if(n->vhaute<=alpha){
                return n->vhaute;
            }
            alpha=maxi(alpha,n->vbasse);
            beta=mini(beta,n->vhaute);
        }
    }
    //printf("ici\n");
    //si on est sur un noeud terminal
    if(prof==0 || testFin(damier)){

        return heuristique(damier,joueur);
    }

    if(maxnode){

        val=MINI;
        v=MINI;
        //on parcours tout les coups valides
        for(int i(-1);i<8;i++){
            for(int j(0);j<8;j++){//pas optimal

                if(estValide(damier,joueur,i,j)){

                    if(val<beta){
                        Damier* fils=new Damier(*damier);
                        joueCoup(fils,joueur,i,j);
                        v=alphaBeta(ttable,fils,joueur,prof-1,alpha,beta,false);
                        if(v>val){
                            val=v;
                            meilleurcoup=i*10+j;
                        }
                        alpha=maxi(alpha,val);
                        delete fils;
                    }
                    else{//elagage beta
                        i=8;
                        j=8;
                        //on met a jour notre table
                        (*ttable)[cle]->vhaute=val;
                    }

                }
            }
        }

    }
    else{ //noeud min code similaire a maxnode

        val=MAXI;
        v=MAXI;
        for(int i(-1);i<8;i++){
            for(int j(0);j<8;j++){//pas optimal

                if(estValide(damier,3-joueur,i,j)){

                    if(val>alpha){
                        Damier* fils=new Damier(*damier);
                        joueCoup(fils,3-joueur,i,j);

                        v=alphaBeta(ttable,fils,joueur,prof-1,alpha,beta,true);
                        if(v<val){
                            val=v;
                            meilleurcoup=i*10+j;
                        }
                        beta=mini(val,beta);
                        delete fils;
                    }
                    else{
                        i=8;
                        j=8;
                        (*ttable)[cle]->vbasse=val;

                    }
                }
            }
        }
    }
    //si notre valeur a ete calculee jusqu au bout -> maj de la table
    if(val>alpha && val<beta){

        (*ttable)[cle]->vbasse=val;
        (*ttable)[cle]->vhaute=val;
    }

    (*ttable)[cle]->real_key=lcle;
    (*ttable)[cle]->distance=prof;
    (*ttable)[cle]->mc=meilleurcoup;

    return val;
}


