#include "IA_MTDf.h"

int MTD(int& f,Table& ttable,Damier& root,int joueur,char prof,int& coup, int (*heuristique)(Damier&, int),time_t tmax,time_t t0)
{
    int val=f;
    int haute=MAXI;
    int basse=MINI;
    int x;
	
    while(haute > basse)
    {
        if(val == basse){
            x=val+1;
        }
        else{
            x=val;
        }
        //on lance un alphabeta avec une fenetre nulle, il retourne donc forcement une upperbound ou une lowerbound
		try {
			val = alphaBetaTT(ttable, root, joueur, prof, x - 1, x,coup, heuristique, tmax, t0);
		}
		catch (char const* fin) {
			throw fin;
		}

        if(val<x){
            haute=val;
        }
        else{
            basse=val;
        }
    }

    f=val;

    return val;
}
