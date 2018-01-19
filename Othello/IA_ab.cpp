#include "IA_ab.h"

int alphaBeta(const Damier& damier,int joueur,char prof,int alpha,int beta,int& meilleurcoup,bool maxnode)
{

    std::vector<int> coups;
    int best,v,mc; //best est notre meilleur score, v la valeur retournée par alphabeta, mc le meilleurcoup

    //si on a atteint une feuille de l'arbre
    if(prof==0 || testFin(damier)){
        return heuristiqueMilieuDePartie(damier,joueur);
    }

    if(maxnode){

        best=MINI;
        v=MINI;

        //on actualise coups pour contenir les coups possibles,
        possibilites(coups,damier,joueur);
		int i(-1), j(0);
        for(auto c : coups){

			i = c / 10;
			j = c % 10;
            Damier* fils=new Damier(damier);
            joueCoup(*fils,joueur,i,j);

            v=alphaBeta(*fils,joueur,prof-1,alpha,beta,meilleurcoup,false);

            delete fils;

            if(v>best){
                best=v;
                mc=c;
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
        possibilites(coups,damier,3-joueur);
		int i(-1), j(0);
        for(auto c : coups){

			i = c / 10;
			j = c % 10;
            Damier* fils=new Damier(damier);
            joueCoup(*fils,3-joueur,i,j);

            v=alphaBeta(*fils,joueur,prof-1,alpha,beta,meilleurcoup,true);

            delete fils;

            if(v<best){
                best=v;
                mc=c;
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


