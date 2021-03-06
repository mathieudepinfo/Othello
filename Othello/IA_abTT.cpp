#include "IA_abTT.h"

using namespace std;

int alphaBetaTT(Table& ttable,const Damier& damier,int joueur,char prof,int alpha,int beta,int& coup, int (*heuristique)(const Damier&, int), time_t tmax, time_t t0,bool maxnode)
{

	if ( (time(NULL) - t0) > tmax) {
		throw "fini";
	}
    int best,v,a,b,mc(-10);

    //on regarde si le noeud est dans la table
    unsigned long lcle=hashage(damier,joueur);
    unsigned int cle=static_cast<unsigned int>(lcle) % TABLE_SIZE;

    if((ttable.isIn(cle))				//si la cle est dans la table
    && (ttable[cle]->getK() == lcle)	//si la cle r�elle correspond bien
    && (ttable[cle]->getD() >= prof)){	//si la profondeur restante est plus petite que lors du stockage des donn�es
		
        if(ttable[cle]->getL() >= beta) return ttable[cle]->getL();	
        if(ttable[cle]->getU() <= alpha) return ttable[cle]->getU();

        alpha = maxi(alpha,ttable[cle]->getL());
        beta = mini(beta,ttable[cle]->getU());
    }

    if(prof == 0 || testFin(damier)){
        return heuristique(damier,joueur);
    }

	vector<int> coups;

    if(maxnode){

        best=MINI;
        v=MINI;
        //ici on ne peut pas modifier directement alpha car on en a besoin a la fin
        a=alpha;

		possibilites(coups, damier, joueur);
		
		int k(-1),l(0);
        for(auto c : coups){
			k = c / 10;
			l = c % 10;
            Damier* fils=new Damier(damier);
            joueCoup(*fils,joueur,k,l);

            v=alphaBetaTT(ttable,*fils,joueur,prof-1,a,beta,mc,heuristique,tmax,t0,false);

            delete fils;

            if(v>best){
                best=v;
                coup=c;
				
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

		possibilites(coups, damier, 3 - joueur);
		
		int k(-1),l(0);
        for(auto c : coups){

			k = c / 10;
			l = c % 10;

            Damier* fils=new Damier(damier);
            joueCoup(*fils,3-joueur,k,l);

            v=alphaBetaTT(ttable,*fils,joueur,prof-1,alpha,b,mc,heuristique,tmax,t0,true);

            delete fils;

            if(v<best){
                best=v;
                coup=c;
				
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
        ttable.store(cle,lcle,prof,coup,best,'l'); 
    }
    else if(best>=beta){
        ttable.store(cle,lcle,prof,coup,best,'u');
    }
    else{
        ttable.store(cle,lcle,prof,coup,best,'e');
    }

    return best;
}
