#include "IA_abTT.h"

using namespace std;

int alphaBetaTT(Table& ttable,Damier& damier,int joueur,char prof,int alpha,int beta, int (*heuristique)(Damier&, int),bool maxnode)
{

    int best,v,meilleurcoup(-10),a,b;

    //on regarde si le noeud est dans la table
    unsigned int lcle=hashage(damier,joueur);
    unsigned int cle=lcle%TABLE_SIZE;

    if((ttable.isIn(cle))				//si la cle est dans la table
    && (ttable[cle]->getK() == lcle)	//si la cle réelle correspond bien
    && (ttable[cle]->getD() >= prof)){	//si la profondeur restante est plus petite que lors du stockage des données

        if(ttable[cle]->getL() >= beta) return ttable[cle]->getL();	
        if(ttable[cle]->getU() <= alpha) return ttable[cle]->getU();

        alpha=maxi(alpha,ttable[cle]->getL());
        beta=mini(beta,ttable[cle]->getU());
    }


    if(prof == 0){
        return heuristique(damier,joueur);
    }

	vector<int>* coups=new vector<int>();

    if(maxnode){

        best=MINI;
        v=MINI;
        //ici on ne peut pas modifier directement alpha car on en a besoin a la fin
        a=alpha;

		possibilites(*coups, damier, joueur);

		int k(-1),l(0);
        for(auto c : *coups){
			k = c / 10;
			l = c % 10;
            Damier* fils=new Damier(damier);
            joueCoup(*fils,joueur,k,l);

            v=alphaBetaTT(ttable,*fils,joueur,prof-1,a,beta,heuristique,false);

            delete fils;

            if(v>best){
                best=v;
                meilleurcoup=c;
				
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

		possibilites(*coups, damier, 3 - joueur);
        
		int k(-1),l(0);
        for(auto c : *coups){

			k = c / 10;
			l = c % 10;

            Damier* fils=new Damier(damier);
            joueCoup(*fils,3-joueur,k,l);

            v=alphaBetaTT(ttable,*fils,joueur,prof-1,alpha,b,heuristique,true);

            delete fils;

            if(v<best){
                best=v;
                meilleurcoup=c;
				
            }

            b=mini(b,beta);

            //fail high
            if(b<=alpha){
			
                break;
            }
			
        }
    }

	//on stocke les infos dans la table
    if(best<=alpha){
        ttable.store(cle,lcle,prof,meilleurcoup,best,'l'); 
    }
    else if(best>=beta){
        ttable.store(cle,lcle,prof,meilleurcoup,best,'u');
    }
    else{
        ttable.store(cle,lcle,prof,meilleurcoup,best,'e');
    }

	
	delete coups;

    return best;
}
