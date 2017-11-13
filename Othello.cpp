#include "Othello.h"
#include <unistd.h>
using namespace std;

bool estValide(Damier& damier,int joueur,int k,int l)
{
    //si on souhaite passer
    if(k<0){
        for(int i(0);i<8;i++){
            for(int j(0);j<8;j++){
                if(estValide(damier,joueur,i,j)){
                    return false;
                }
            }
        }
        return true;
    }

    //s'il y a deja un jeton sur la case
    if(damier.getV(k,l)==1 || damier.getV(k,l)==2){
        return false;
    }

    int d[3]={-1,0,1};//directions
    bool pion_adv;
    int cpt;

    for(int i(0);i<3;i++){
        for(int j(0);j<3;j++){

            if(d[i]!=0 || d[j]!=0){

                pion_adv=false;
                cpt=1;

                //on parcours une direction, il faut qu'on trouve un pion adverse puis un pion allie
                while(0<=(k+cpt*d[i]) && (k+cpt*d[i])<8 && 0<=(l+cpt*d[j]) && (l+cpt*d[j])<8
                   && damier.getV(k+cpt*d[i],l+cpt*d[j])==3-joueur){

                    cpt++;
                    pion_adv=true; //on a rencontre un pion adverse
                }

                if(0<=(k+cpt*d[i]) && (k+cpt*d[i])<8 && 0<=(l+cpt*d[j]) && (l+cpt*d[j])<8
                   && pion_adv
                   && damier.getV(k+cpt*d[i],l+cpt*d[j])==joueur){

                    return true;
                }
            }
        }
    }
    return false;
}

void joueCoup(Damier& damier,int joueur, int k,int l)
{
    //si on ne veut pas passer
    if(k>=0){

        damier.iNp();
        damier.setV(joueur,k,l);

        int d[3]={-1,0,1};
        bool p_adv;
        int cpt;
        //on mange les pions
        for(int i(0);i<3;i++){
            for(int j(0);j<3;j++){
                if(d[i]!=0 || d[j]!=0){

                    p_adv=false,
                    cpt=1;

                    //on parcours une direction, il faut qu'on trouve un pion adverse puis un pion allie
                    while( 0<=(k+cpt*d[i]) && (k+cpt*d[i])<8 && 0<=(l+cpt*d[j]) && (l+cpt*d[j])<8
                        && damier.getV(k+cpt*d[i],l+cpt*d[j])==3-joueur){
                        cpt++;
                        p_adv=true;
                    }

                    if(0<=(k+cpt*d[i]) && (k+cpt*d[i])<8 && 0<=(l+cpt*d[j]) && (l+cpt*d[j])<8
                    && p_adv
                    && damier.getV(k+cpt*d[i],l+cpt*d[j])==joueur){
                        for(int m(1);m<cpt;m++){ //on mange tous les pions rencontres

                            damier.setV(joueur,k+m*d[i],l+m*d[j]);
                        }
                    }
                }
            }
        }
    }

}

bool testFin(Damier& damier)
{
    for(int joueur(1);joueur<3;joueur++){
        for(int i(0);i<8;i++){
            for(int j(0);j<8;j++){
                //si le moindre coup est possible on a pas fini
                if(estValide(damier,joueur,i,j)){
                    return false;
                }
            }
        }
    }
    return true;
}

int score(Damier& damier, int joueur)
{
    int cpt(0);
    for(int i(0);i<8;i++){
        for(int j(0);j<8;j++){

            if(damier.getV(i,j)==joueur){
                    cpt++;
            }
        }
    }
    return cpt;
}


