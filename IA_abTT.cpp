#include "IA_abTT.h"

int alphaBetaTT(Table& ttable,Damier& damier,int joueur,char prof,int alpha,int beta,bool maxnode)
{
    int coups[64][2]={0};
    int best,v,meilleurcoup(-10),n_coups,a,b;

    //on regarde si le noeud est dans la table
    unsigned int lcle=hashage(damier,joueur);
    unsigned int cle=lcle%TABLE_SIZE;

    if((ttable.isIn(cle))
    && (ttable[cle]->getK()==lcle)
    && (ttable[cle]->getD()>=prof)){

        if(ttable[cle]->getL()>=beta) return ttable[cle]->getL();
        if(ttable[cle]->getU()<=alpha) return ttable[cle]->getU();

        alpha=maxi(alpha,ttable[cle]->getL());
        beta=mini(beta,ttable[cle]->getU());
    }

    if(prof==0){

        return heuristique(damier,joueur);
    }

    if(maxnode){

        best=MINI;
        v=MINI;
        //ici on ne peut pas modifier directement alpha car on en a besoin a la fin
        a=alpha;

        possibilites(coups,damier,n_coups,joueur);

        for(int c(0);c<n_coups;c++){

            Damier* fils=new Damier(damier);
            joueCoup(*fils,joueur,coups[c][0],coups[c][1]);

            v=alphaBetaTT(ttable,*fils,joueur,prof-1,a,beta,false);

            delete fils;

            if(v>best){
                best=v;
                meilleurcoup=coups[c][0]*10+coups[c][1];
            }

            a=maxi(a,best);
            //fail low
            if(a>=beta){
                break;;
            }
        }
    }
    else{

        best=MAXI;
        v=MAXI;
        b=beta;

        possibilites(coups,damier,n_coups,3-joueur,ttable,cle);

        for(int c(0);c<n_coups;c++){

            Damier* fils=new Damier(damier);
            joueCoup(*fils,3-joueur,coups[c][0],coups[c][1]);

            v=alphaBetaTT(ttable,*fils,joueur,prof-1,alpha,b,true);

            delete fils;

            if(v<best){
                best=v;
                meilleurcoup=coups[c][0]*10+coups[c][1];
            }

            b=mini(b,beta);
            //fail high
            if(b<=alpha){
                break;
            }
        }
    }

    if(best<=alpha){
        ttable.store(cle,lcle,prof,meilleurcoup,best,'l');
    }
    else if(best>=beta){
        ttable.store(cle,lcle,prof,meilleurcoup,best,'u');
    }
    else{
        ttable.store(cle,lcle,prof,meilleurcoup,best,'e');
    }

    return best;
}
