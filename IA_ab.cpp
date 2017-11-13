#include "IA_main.h"
#include "IA_ab.h"
#define MAXI 2147483647
#define MINI -2147483648

using namespace std;

int alphaBeta(Damier& damier,int joueur,char prof,int alpha,int beta,int& meilleurcoup,bool maxnode)
{

    int coups[64][2];
    int best,v,n_coups,mc;

    //si on a atteint une feuille de l'arbre
    if(prof==0 || testFin(damier)){
        return heuristique(damier,joueur);
    }

    if(maxnode){

        best=MINI;
        v=MINI;

        //on actualise coups pour contenir les coups possibles,
        possibilites(coups,damier,n_coups,joueur);

        for(int c(0);c<n_coups;c++){

            Damier* fils=new Damier(damier);
            joueCoup(*fils,joueur,coups[c][0],coups[c][1]);

            v=alphaBeta(*fils,joueur,prof-1,alpha,beta,meilleurcoup,false);

            delete fils;

            if(v>best){
                best=v;
                mc=coups[c][0]*10+coups[c][1];
            }

            alpha=maxi(alpha,best);
            //coupure alpha
            if(alpha>=beta){
                break;
            }
        }
    }
    else{ //noeud min code similaire a maxnode

        best=MAXI;
        v=MAXI;

        //cette fois on prend les possibilités de l'adversaire
        possibilites(coups,damier,n_coups,3-joueur);
        for(int c(0);c<n_coups;c++){

            Damier* fils=new Damier(damier);
            joueCoup(*fils,3-joueur,coups[c][0],coups[c][1]);

            v=alphaBeta(*fils,joueur,prof-1,alpha,beta,meilleurcoup,true);

            delete fils;

            if(v<best){
                best=v;
                mc=coups[c][0]*10+coups[c][1];
            }

            beta=mini(best,beta);
            //coupure beta
            if(beta<=alpha){
                break;
            }
        }
    }

    meilleurcoup=mc;

    return best;
}


