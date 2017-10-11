#include "Othello.h"

using namespace std;

bool estValide(Damier* _damier,int joueur,int k,int l)
{

    //si on souhaite passer
    if(k<0){

        for(int i(0);i<8;i++){
            for(int j(0);j<8;j++){
                if(estValide(_damier,joueur,i,j)){
                    return false;
                }
            }
        }
        return true;
    }

    //s'il y a deja n jeton sur la case
    if(_damier->getV(k,l)==1 || _damier->getV(k,l)==2){
        return false;
    }

    int d[3]={-1,0,1};//directions
    for(int i(0);i<3;i++){
        for(int j(0);j<3;j++){

            if(d[i]!=0 || d[j]!=0){
                bool pion_adv(false);
                int cpt(1);

                //on parcours une direction, il faut qu'on trouve un pion adverse puis un pion allie
                while(0<=(k+cpt*d[i]) && (k+cpt*d[i])<8 && 0<=(l+cpt*d[j]) && (l+cpt*d[j])<8
                   && _damier->getV(k+cpt*d[i],l+cpt*d[j])==3-joueur){

                    cpt++;
                    pion_adv=true; //on a rencontre un pion adverse
                }

                if(   0<=(k+cpt*d[i]) && (k+cpt*d[i])<8 && 0<=(l+cpt*d[j]) && (l+cpt*d[j])<8
                   && pion_adv
                   && _damier->getV(k+cpt*d[i],l+cpt*d[j])==joueur){

                    return true;
                }
            }
        }
    }

    return false;
}

void joueCoup(Damier* _damier,int joueur, int k,int l)
{
    //si on ne veut pas passer
    if(k>=0){
        _damier->setV(joueur,k,l);
        //on mange les pions
        int d[3]={-1,0,1};
        for(int i(0);i<3;i++){
            for(int j(0);j<3;j++){
                if(d[i]!=0 || d[j]!=0){

                    bool p_adv(false);
                    int cpt(1);

                    //on parcours une direction, il faut qu'on trouve un pion adverse puis un pion allie
                    while( 0<=(k+cpt*d[i]) && (k+cpt*d[i])<8 && 0<=(l+cpt*d[j]) && (l+cpt*d[j])<8
                        && _damier->getV(k+cpt*d[i],l+cpt*d[j])==3-joueur){
                        cpt++;
                        p_adv=true;
                    }

                    if(0<=(k+cpt*d[i]) && (k+cpt*d[i])<8 && 0<=(l+cpt*d[j]) && (l+cpt*d[j])<8
                    && p_adv
                    && _damier->getV(k+cpt*d[i],l+cpt*d[j])==joueur){
                        for(int m(1);m<cpt;m++){ //on mange tous les pions rencontres

                            _damier->setV(joueur,k+m*d[i],l+m*d[j]);
                        }
                    }
                }
            }
        }
    }

}

bool testFin(Damier* _damier)
{
    for(int joueur(1);joueur<3;joueur++){
        for(int i(0);i<8;i++){
            for(int j(0);j<8;j++){
                //si le moindre coup est possible on a pas fini
                if(estValide(_damier,joueur,i,j)){
                    return false;
                }
            }
        }
    }
    return true;
}

int score(Damier* _damier, int joueur)
{
    int cpt(0);
    for(int i(0);i<8;i++){
        for(int j(0);j<8;j++){

            if(_damier->cases[i][j]==joueur){
                    cpt++;
            }
        }
    }
    return cpt;
}


